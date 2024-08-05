#include <Novice.h>
#include "MT3.h"
const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 rotate{ 0.0f, 0.0f, 0.0f };//回転
	Vector3 translate{ 0.0f, 0.0f, 0.0f };//移動
	Vector3 scale{ 1.0f, 1.0f, 1.0f };//拡縮

	Vector3    rotate2{ 0.0f, 0.0f, 0.0f };//回転
	Vector3 translate2{ 0.0f, 0.0f, 0.0f };//移動

	Vector3 cameraScale{ 1.0f, 1.0f, 1.0f };//拡縮
	Vector3 cameraRotate{ 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate{ 0.0f,0.0f,-0.5f };
	Matrix4x4 worldMatrix;

	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;//カメラのビュー行列

	//透視投影行列(同次クリップ空間)
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewPortMatrix;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
