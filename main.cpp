#define _USE_MATH_DEFINES
#include <Novice.h>
#include"MatrixFunction.h"
#include"Vector3.h"
#include"iostream"


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

	MatrixFunction* matFunc;
	matFunc = new MatrixFunction;

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = matFunc->Cross(v1, v2);

	Vector3 rotate{ 0.0f, 0.0f, 0.0f };//回転
	Vector3 translate{ 0.0f, 0.0f, 0.0f };//移動
	Vector3 scale{ 0.125f, 0.125f, 0.125f };//拡縮

	Vector3 cameraScale{ 1.0f, 1.0f, 1.0f };//拡縮
	Vector3 cameraRotate{ 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate{ 0.0f,0.0f,-5.0f };
	Matrix4x4 worldMatrix;

	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;//カメラのビュー行列

	//透視投影行列(同次クリップ空間)
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewPortMatrix;


	//Screen空間へと頂点を変換する
	Vector3 kLocalVertices[3] = {
		{0.0f,0.5f,0.0f},
		{0.5f,-0.5f,0.0f},
		{-0.5f,-0.5f,0.0f},
	};//ローカル座標

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
		rotate.y += 0.04f;
		if (Novice::CheckHitKey(DIK_A)) {
			translate.x -= 0.005f;
		}
		else if (Novice::CheckHitKey(DIK_D)) {
			translate.x += 0.005f;
		}

		if (Novice::CheckHitKey(DIK_W)) {
			translate.z += 0.005f;
		}
		else if (Novice::CheckHitKey(DIK_S)) {
			translate.z -= 0.005f;
		}



		//各種行列の計算(レンダリングパイプライン)
		worldMatrix = matFunc->MakeAffineMatrix(scale, rotate, translate);
		cameraMatrix = matFunc->MakeAffineMatrix(cameraScale, cameraRotate, { 0,0,-0.5f });//カメラ行列
		viewMatrix = matFunc->Inverse(cameraMatrix);//カメラのビュー行列

		//透視投影行列(同次クリップ空間)
		projectionMatrix = matFunc->MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = matFunc->Multiply(worldMatrix, matFunc->Multiply(viewMatrix, projectionMatrix));
		viewPortMatrix = matFunc->MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 screenVertices1[3] = {
matFunc->Transform(matFunc->Transform(kLocalVertices[0],worldViewProjectionMatrix),viewPortMatrix),
matFunc->Transform(matFunc->Transform(kLocalVertices[1],worldViewProjectionMatrix),viewPortMatrix),
matFunc->Transform(matFunc->Transform(kLocalVertices[2],worldViewProjectionMatrix),viewPortMatrix),
		};


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここか
		/// 

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");
		VectorScreenPrintf(1000, 0, cross, "Cross");
		Novice::DrawTriangle(
			int(screenVertices1[0].x),
			int(screenVertices1[0].y),
			int(screenVertices1[1].x),
			int(screenVertices1[1].y),
			int(screenVertices1[2].x),
			int(screenVertices1[2].y),
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
	delete matFunc;
	Novice::Finalize();
	return 0;
}
