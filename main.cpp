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

	Sphere sphere = {
		{0,0,0},0.5f
	};

	uint32_t sphereColor = WHITE;

	Plane plane = {
		{0,1.0f,0},0
	};
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
		if (IsCollision(sphere, plane)) {
			sphereColor = RED;
		}
		else {
			sphereColor = WHITE;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldviewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, worldviewProjectionMatrix, viewportMatrix, sphereColor);
		DrawPlane(plane, worldviewProjectionMatrix, viewportMatrix, WHITE);
		ImGui::Begin("Window");
		ImGui::DragFloat3("sphere1Center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphere1Radius", &sphere.radius, 0.01f);

		ImGui::End();

		ImGui::Begin("Window2");
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("PlaneDistance", &plane.distance, 0.01f);
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
