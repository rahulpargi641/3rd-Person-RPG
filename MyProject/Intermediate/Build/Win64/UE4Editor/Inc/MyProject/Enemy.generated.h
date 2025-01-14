// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AMainCharacter;
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef MYPROJECT_Enemy_generated_h
#error "Enemy.generated.h already included, missing '#pragma once' in Enemy.h"
#endif
#define MYPROJECT_Enemy_generated_h

#define MyProject_Source_MyProject_Enemy_h_24_SPARSE_DATA
#define MyProject_Source_MyProject_Enemy_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execMoveToTarget); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapBegin); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapBegin);


#define MyProject_Source_MyProject_Enemy_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMoveToTarget); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execCombatSphereOnOverlapBegin); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapEnd); \
	DECLARE_FUNCTION(execAgroSphereOnOverlapBegin);


#define MyProject_Source_MyProject_Enemy_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define MyProject_Source_MyProject_Enemy_h_24_INCLASS \
private: \
	static void StaticRegisterNativesAEnemy(); \
	friend struct Z_Construct_UClass_AEnemy_Statics; \
public: \
	DECLARE_CLASS(AEnemy, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AEnemy)


#define MyProject_Source_MyProject_Enemy_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEnemy(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEnemy) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public:


#define MyProject_Source_MyProject_Enemy_h_24_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEnemy(AEnemy&&); \
	NO_API AEnemy(const AEnemy&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemy); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemy)


#define MyProject_Source_MyProject_Enemy_h_24_PRIVATE_PROPERTY_OFFSET
#define MyProject_Source_MyProject_Enemy_h_21_PROLOG
#define MyProject_Source_MyProject_Enemy_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MyProject_Source_MyProject_Enemy_h_24_PRIVATE_PROPERTY_OFFSET \
	MyProject_Source_MyProject_Enemy_h_24_SPARSE_DATA \
	MyProject_Source_MyProject_Enemy_h_24_RPC_WRAPPERS \
	MyProject_Source_MyProject_Enemy_h_24_INCLASS \
	MyProject_Source_MyProject_Enemy_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define MyProject_Source_MyProject_Enemy_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MyProject_Source_MyProject_Enemy_h_24_PRIVATE_PROPERTY_OFFSET \
	MyProject_Source_MyProject_Enemy_h_24_SPARSE_DATA \
	MyProject_Source_MyProject_Enemy_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Enemy_h_24_INCLASS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Enemy_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class AEnemy>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MyProject_Source_MyProject_Enemy_h


#define FOREACH_ENUM_EENEMYMOVEMENTSTATUS(op) \
	op(EEnemyMovementStatus::EMS_Idle) \
	op(EEnemyMovementStatus::EMS_MoveToTarget) \
	op(EEnemyMovementStatus::EMS_Attacking) 

enum class EEnemyMovementStatus : uint8;
template<> MYPROJECT_API UEnum* StaticEnum<EEnemyMovementStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
