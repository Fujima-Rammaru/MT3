#include <Novice.h>
#include"MatrixFunction.h"

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


	// Windowsアプリでのエントリーポイント(main関数)
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

		MatrixFunction* matrixFunction;
		matrixFunction = new MatrixFunction;

		// ライブラリの初期化
		Novice::Initialize(kWindowTitle, 1280, 720);

		Vector3 translate = { 4.1f,2.6f,0.8f };
		Vector3 scale = { 1.5f,5.2f,7.3f };


		Matrix4x4 translatematrix = matrixFunction->MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = matrixFunction->MakeScaleMatrix(scale);

		Vector3 point = { 2.3f,3.8f,1.4f };

		Matrix4x4 transformMatrix = {
			1.0f,2.0f,3.0f,4.0f,
			3.0f,1.0f,1.0f,2.0f,
			1.0f,4.0f,2.0f,3.0f,
			2.0f,2.0f,1.0f,3.0f,
		};

		Vector3 transformed = matrixFunction->Transform(point, transformMatrix);
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
