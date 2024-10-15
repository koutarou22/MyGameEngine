#include"Model.h"
#include"Engine/Direct3D.h"

namespace Model
{
	std::vector<ModelData*> modelList;
}
int Model::Load(std::string filename)
{
	//ファイル名のモデルを読み込む
	ModelData* pData = new ModelData;
	pData->filename_ = filename;
	pData->pFbx_ = nullptr;

	for (auto& e : modelList)
	{
		if (e->filename_ == filename)//読み込み済み
		{
			pData->pFbx_ = e->pFbx_;
			break; //同名のファイルが読み込み済み
		}
	}
	if (pData->pFbx_ == nullptr)//同名のファイルがリストになかったら
	{
		pData->pFbx_ = new FBX;
		pData->pFbx_->Load(filename);
	}
	modelList.push_back(pData);
	//同じモデルがすでに読み込まれていたら、エラー　-1を返す

	return(modelList.size() - 1);
	//初めての読み込みだったら、モデルを読み込んで、配列を追加
}
void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}
void Model::Draw(int hModel)
{
	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_);
}
void Model::Release()
{
	bool isRefered = false;
	for (int j = 0; j < modelList.size(); j++)
	{
		for (int i = j+1; i < modelList.size(); i++)//全部やっちゃダメ、0以上からスタートしないといけない　対象がない
		{
			if (modelList[j]->pFbx_ == modelList[i]->pFbx_)
			{
				isRefered = true;
				break;
			}
		}
		if (isRefered == false)
		{
			SAFE_DELETE(modelList[j]->pFbx_);
		}
		SAFE_DELETE(modelList[j]);
	}
	modelList.clear();//参照しているものがなければクリアする
}
