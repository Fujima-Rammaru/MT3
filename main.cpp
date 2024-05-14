#include <Novice.h>
#include"MatrixFunction.h"
#include"Vector3.h"

const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

//4x4行列の数値表示
static void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* functionName) {
	Novice::ScreenPrintf(x, y, functionName);

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 17, "%6.02f", matrix.m[row][column]);
		}
	}
}

//３次元ベクトルの数値表現
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	MatrixFunction* matrixFunction;
	matrixFunction = new MatrixFunction;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 rotate{ 1.2f, -3.9f, 2.5f };//回転
	Vector3 translate{ 2.8f, 0.4f, -1.3f };//移動
	Vector3 scale{ 1.0f, 1.0f, 1.0f };//拡縮
	Vector3 camaraPosition{ 1.0f, 1.0f, 1.0f };//カメラの座標


	//各種行列の計算
	Matrix4x4 worldMatrix = matrixFunction->MakeAffineMatrix(scale, rotate, translate);
	Matrix4x4 camaraMatrix = matrixFunction->MakeAffineMatrix(scale,{0.0f,0.0f,0.0f}, translate);
	Matrix4x4 viewMatrix=matrixFunction->
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
	delete matrixFunction;
	Novice::Finalize();
	return 0;
}
