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

	Sphere spheres[2];
	spheres[0].center = { 0,0,0 };
	spheres[1].center = { 0.5f,0.2f,0.2f };
	spheres[0].radius = 0.5f;
	spheres[1].radius = 0.5f;
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldviewProjectionMatrix, viewportMatrix);

		DrawSphere(spheres[1], worldviewProjectionMatrix, viewportMatrix, WHITE);

		if (IsCollision(spheres[0], spheres[1])) {
			DrawSphere(spheres[0], worldviewProjectionMatrix, viewportMatrix, RED);

		}
		else {
			DrawSphere(spheres[0], worldviewProjectionMatrix, viewportMatrix, WHITE);
		}
		ImGui::Begin("Window");
		ImGui::DragFloat3("sphere1Center", &spheres[0].center.x, 0.01f);
		ImGui::DragFloat("sphere1Radius", &spheres[0].radius, 0.01f);
		ImGui::DragFloat3("sphere2Center", &spheres[1].center.x, 0.01f);
		ImGui::DragFloat("sphere2Radius", &spheres[1].radius, 0.01f);
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
