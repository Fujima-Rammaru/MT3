#include <Novice.h>
#include "MT3.h"
#include"imgui.h"
const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Novice::Initialize(kWindowTitle, kWindowWidth,kWindowHeight);

	Vector3 rotate{ 0.0f, 0.0f, 0.0f };//回転
	Vector3 translate{ 0.0f, 0.0f, 0.0f };//移動
	Vector3 scale{ 1.0f, 1.0f, 1.0f };//拡縮

	Vector3 cameraScale{ 1.0f, 1.0f, 1.0f };//拡縮
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Matrix4x4 worldMatrix;

	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;//カメラのビュー行列

	//透視投影行列(同次クリップ空間)
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewPortMatrix;

	Sphere sphere = {
		{0.0f,0.0f,0.0f},0.7f
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

		//各種行列の計算(レンダリングパイプライン)
		worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);//カメラ行列
		viewMatrix = Inverse(cameraMatrix);//カメラのビュー行列

		//透視投影行列(同次クリップ空間)
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = MultiplyMat(worldMatrix, MultiplyMat(viewMatrix, projectionMatrix));
		viewPortMatrix = MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawSphere(sphere, worldViewProjectionMatrix, viewPortMatrix, BLACK);
		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
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
