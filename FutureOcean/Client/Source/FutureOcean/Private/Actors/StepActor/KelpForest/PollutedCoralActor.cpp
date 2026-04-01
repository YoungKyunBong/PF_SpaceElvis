#include "Actors/StepActor/KelpForest/PollutedCoralActor.h"
#include "Manager/CoralForest/PollutedCoralManager.h"
#include "Manager/KelpForest/Wall_KelpForestManager.h"


void APollutedCoralActor::Init(AWall_KelpForestManager* _manager)
{
	MaterialCount = SMC_PollutedCoral->GetNumMaterials();
	for (int i = 0; i < MaterialCount; ++i) {
		MInsDyns.Add(SMC_PollutedCoral->CreateDynamicMaterialInstance(i));
	}
	WallManager = _manager;
	
}

void APollutedCoralActor::TempSetMesh(UMaterialInterface* _DefaultWidgetClass)
{
	//Construction Script 에디터 시점에서 설정하는 값
	SMC_PollutedCoral->SetStaticMesh(TempMesh);

	/*MaterialCount = SMC_PollutedCoral->GetNumMaterials();

	for (int i = 0; i < MaterialCount; ++i) {
		SMC_PollutedCoral->SetMaterial(i, _DefaultWidgetClass);
	}*/
}

void APollutedCoralActor::ChangeOpValue(int32 _OilCount)
{
	OpValue += (OpChangeValue / _OilCount);
	
	for (int i = 1; i < MaterialCount; ++i) {
		MInsDyns[i]->SetScalarParameterValue(ParameterName, OpValue);
	}


	if (Tags.Contains("TypeAB"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("A_BGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeBB"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("B_BGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeCB"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("C_BGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeDB"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("D_BGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeAS"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("A_SGrow_Int", OpValue);
		}

		// 임시 타입 설정 후 변경 해야 함
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("B_SGrow_Int", OpValue);
		}
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("C_SGrow_Int", OpValue);
		}
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("D_SGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeBS"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("B_SGrow_Int", OpValue);
		}
	}
	else if (Tags.Contains("TypeCS"))
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("C_SGrow_Int", OpValue);
		}
	}
	else
	{
		for (int i = 0; i < MaterialCount; ++i) {
			MInsDyns[i]->SetScalarParameterValue("D_SGrow_Int", OpValue);
		}
	}
	
	
	
	
	
	
}
