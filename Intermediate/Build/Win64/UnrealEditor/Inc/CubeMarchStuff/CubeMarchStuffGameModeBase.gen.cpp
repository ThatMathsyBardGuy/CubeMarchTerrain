// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CubeMarchStuff/Public/CubeMarchStuffGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCubeMarchStuffGameModeBase() {}
// Cross Module References
	CUBEMARCHSTUFF_API UClass* Z_Construct_UClass_ACubeMarchStuffGameModeBase_NoRegister();
	CUBEMARCHSTUFF_API UClass* Z_Construct_UClass_ACubeMarchStuffGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_CubeMarchStuff();
// End Cross Module References
	void ACubeMarchStuffGameModeBase::StaticRegisterNativesACubeMarchStuffGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ACubeMarchStuffGameModeBase_NoRegister()
	{
		return ACubeMarchStuffGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_CubeMarchStuff,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering LOD WorldPartition DataLayers Utilities|Transformation" },
		{ "IncludePath", "CubeMarchStuffGameModeBase.h" },
		{ "ModuleRelativePath", "Public/CubeMarchStuffGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACubeMarchStuffGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::ClassParams = {
		&ACubeMarchStuffGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACubeMarchStuffGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACubeMarchStuffGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACubeMarchStuffGameModeBase, 3090395422);
	template<> CUBEMARCHSTUFF_API UClass* StaticClass<ACubeMarchStuffGameModeBase>()
	{
		return ACubeMarchStuffGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACubeMarchStuffGameModeBase(Z_Construct_UClass_ACubeMarchStuffGameModeBase, &ACubeMarchStuffGameModeBase::StaticClass, TEXT("/Script/CubeMarchStuff"), TEXT("ACubeMarchStuffGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACubeMarchStuffGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
