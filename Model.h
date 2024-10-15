#include <string>
#include "Engine/Fbx.h"

namespace Model
{
	struct ModelData
	{
		//FBX
		FBX* pFbx_;
		//Transform
		Transform transform_;
		//Filename
		std::string filename_;
		ModelData() :pFbx_(nullptr), filename_("")
		{

		}
	};
	//モデルの一覧を保存する配列(ベクターかリスト?)
	int Load(std::string filename);

	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
}

