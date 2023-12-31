#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathUtilityForText.h"

//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() 
{
	delete spriteBG_; 
	delete modelStage_;
}


//初期化
void GameScene::Initialize() {
	//BG (2D)
	textureHandleBG_ = TextureManager::Load("./Resources/bg.jpg");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();
	//ステージ
	textureHandleStage_ = TextureManager::Load("./Resources/stage.jpg");
	modelStage_ = Model::Create();
	worldTransformStage_.Initialize();
	//ステージの位置を変更
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	//変換行列を更新
	worldTransformStage_.matWorld_ = MakeAffineMatrix(
	    worldTransformStage_.scale_,
		worldTransformStage_.rotation_,
		worldTransformStage_.translation_);
	//変数行列を定数バッファに転送
	worldTransformStage_.TransferMatrix();

}


//更新
void GameScene::Update() {}


//描画
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	spriteBG_->Draw();
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	
	//ステージ
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);

	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
