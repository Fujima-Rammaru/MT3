#include <Novice.h>
#include"MT3.h"
#include"imgui.h"
const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	Vector3 cameraTranslate = { 0.0f,2.0f,-6.0f };
	Vector3 cameraRotate = { 0.32f,0.0f,0.0f };
	Vector3 rotate = { 0,0,0 };
	Vector3 translate = { 0,0,0 };
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 cameraScale = { 1.0f,1.0f,1.0f };

	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewportMatrix = MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	Segment segment{ {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} };
	Plane plane = {
		{0,1.0f,0},0
	};
	uint32_t color = WHITE;
	Vector3 start={};
	Vector3 end={};
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		 viewMatrix = Inverse(cameraMatrix);
		 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		 worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		 viewportMatrix = MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		
		if (IsCollision(segment, plane)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldviewProjectionMatrix, viewportMatrix);
		DrawPlane(plane, worldviewProjectionMatrix, viewportMatrix, WHITE);
		DrawSegment(segment,worldviewProjectionMatrix, viewportMatrix, color);

		ImGui::Begin("Window");
		ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat("plane.distance", &plane.distance, 0.01f);
		ImGui::DragFloat3("plane.normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::End();

		
		
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
