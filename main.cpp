#include <Novice.h>
#include"MatrixFunction.h"
#include"Vector3.h"
#include"iostream"

const char kWindowTitle[] = "GC2A_10_フジマ_ランマル_MT3";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

//4x4行列の数値表示
//static void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* functionName) {
//	Novice::ScreenPrintf(x, y, functionName);
//
//	for (int row = 0; row < 4; row++) {
//		for (int column = 0; column < 4; column++) {
//			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 17, "%6.02f", matrix.m[row][column]);
//		}
//	}
//}

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

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 rotate{ 0.0f, 0.0f, 0.0f };//回転
	Vector3 translate{ 0.0f, 0.0f, 0.0f };//移動
	Vector3 scale{ 1.0f, 1.0f, 1.0f };//拡縮

	//各種行列の計算
	Matrix4x4 worldMatrix = matrixFunction->MakeAffineMatrix(scale, rotate, translate);//ワールド行列
	Matrix4x4 camaraMatrix = matrixFunction->MakeAffineMatrix(scale, { 0.0f,0.0f,0.0f }, translate);
	Matrix4x4 viewMatrix = matrixFunction->Inverse(camaraMatrix);//カメラのビュー行列

	//透視投影行列
	Matrix4x4 projectionMatrix = matrixFunction->MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 10.0f, 100.0f);

	Matrix4x4 worldViewProjectionmatrix = matrixFunction->Multiply(worldMatrix, matrixFunction->Multiply(viewMatrix, projectionMatrix));

	Matrix4x4 viewPortMatrix = matrixFunction->MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	//Screen空間へと頂点を変換する

	Vector3 kLocalVertices[3] = {//ローカル座標系
		{0.1f,0.1f,0.1f,},
		{20.0f,20.0f,0.1f},
		{10.0f,50.0f,0.1f},

	};

	Vector3 screenVertices[3];

	for (int i = 0; i < 3; i++) {
		//NDCまで変換。Transformを使うと同次座標->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		Vector3 ndcVertex = matrixFunction->Transform(kLocalVertices[i], worldViewProjectionmatrix);//正規化デバイス座標系
		//viewport変換を行ってscreen空間へ
		screenVertices[i] = matrixFunction->Transform(ndcVertex, viewPortMatrix);
	}

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = matrixFunction->Cross(v1, v2);

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
		/// ↓描画処理ここか
		/// 

		VectorScreenPrintf(0, 0, cross, "Cross");

		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			RED, kFillModeSolid
		);
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
