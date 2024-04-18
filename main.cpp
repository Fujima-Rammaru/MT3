#include <Novice.h>
#include <Matrix4x4.h>

const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4 m2) {
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];

	result.m[1][0] = m1.m[1][0] + m2.m[0][0];
	result.m[1][1] = m1.m[1][1] + m2.m[0][1];
	result.m[1][2] = m1.m[1][2] + m2.m[0][2];
	result.m[1][3] = m1.m[1][3] + m2.m[0][3];

	result.m[2][0] = m1.m[2][0] + m2.m[0][0];
	result.m[2][1] = m1.m[2][1] + m2.m[0][1];
	result.m[2][2] = m1.m[2][2] + m2.m[0][2];
	result.m[2][3] = m1.m[2][3] + m2.m[0][3];

	result.m[3][0] = m1.m[3][0] + m2.m[0][0];
	result.m[3][1] = m1.m[3][1] + m2.m[0][1];
	result.m[3][2] = m1.m[3][2] + m2.m[0][2];
	result.m[3][3] = m1.m[3][3] + m2.m[0][3];

	return result;
}

//行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4 m2) {
	Matrix4x4 result = { 0 };



	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4 m2) {
	Matrix4x4 result = { 0 };



	return result;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;



	return result;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;



	return result;
}

//単位行列の作成
Matrix4x4 MakeIdentity4x4(const Matrix4x4& m) {
	Matrix4x4 result;



	return result;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix4x4 m1 = {};

	Matrix4x4 m2;

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
	Novice::Finalize();
	return 0;
}
