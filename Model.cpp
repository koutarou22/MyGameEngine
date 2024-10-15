#include"Model.h"
#include"Engine/Direct3D.h"

namespace Model
{
	std::vector<ModelData*> modelList;
}
int Model::Load(std::string filename)
{
	//�t�@�C�����̃��f����ǂݍ���
	ModelData* pData = new ModelData;
	pData->filename_ = filename;
	pData->pFbx_ = nullptr;

	for (auto& e : modelList)
	{
		if (e->filename_ == filename)//�ǂݍ��ݍς�
		{
			pData->pFbx_ = e->pFbx_;
			break; //�����̃t�@�C�����ǂݍ��ݍς�
		}
	}
	if (pData->pFbx_ == nullptr)//�����̃t�@�C�������X�g�ɂȂ�������
	{
		pData->pFbx_ = new FBX;
		pData->pFbx_->Load(filename);
	}
	modelList.push_back(pData);
	//�������f�������łɓǂݍ��܂�Ă�����A�G���[�@-1��Ԃ�

	return(modelList.size() - 1);
	//���߂Ă̓ǂݍ��݂�������A���f����ǂݍ���ŁA�z���ǉ�
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
		for (int i = j+1; i < modelList.size(); i++)//�S���������_���A0�ȏォ��X�^�[�g���Ȃ��Ƃ����Ȃ��@�Ώۂ��Ȃ�
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
	modelList.clear();//�Q�Ƃ��Ă�����̂��Ȃ���΃N���A����
}
