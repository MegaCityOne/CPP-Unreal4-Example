// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Needed by Unreal 4
#include "GameFramework/Pawn.h" // Needed by Unreal 4
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "main_map_camera_pawn.generated.h" // Needed by Unreal 4

UCLASS()
class RES_PUBLICA_API Amain_map_camera_pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Amain_map_camera_pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* RootMesh;				// You have to define this pointer as a class because C++ reasons

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

public:
	void pan_main_map_camera_pawn_x_axis(float AxisValue);
	void pan_main_map_camera_pawn_y_axis(float AxisValue);
	void zoom_in_main_map_camera_pawn();
	void zoom_out_main_map_camera_pawn();

	float camera_movement_scale_x_axis;
	float camera_movement_scale_y_axis;
	float camera_movement_scale_z_axis;
	float camera_speed_x_axis;
	float camera_speed_y_axis;
	float camera_speed_z_axis;
	float camera_movement_x;
	float camera_movement_y;
	float camera_movement_z;
	float zoom_speed_factor;

	bool b_zooming_in;
	bool b_zooming_out;

	FVector camera_input;
};
