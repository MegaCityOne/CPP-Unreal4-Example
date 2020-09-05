// Fill out your copyright notice in the Description page of Project Settings.


#include "main_map_camera_pawn.h"

// Sets default values
Amain_map_camera_pawn::Amain_map_camera_pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<USceneComponent>(TEXT("RootMesh"));
	RootComponent = RootMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootMesh);
	Camera->SetupAttachment(SpringArm);

	SpringArm->bDoCollisionTest = false;
	Camera->SetWorldRotation(FRotator(-80.0f, 0.0f, 0.0f));
	//SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set default camera values
	camera_movement_scale_x_axis = 0.0;
	camera_movement_scale_y_axis = 0.0;
	camera_movement_scale_z_axis = 0.0;
	camera_speed_x_axis = 500.0;
	camera_speed_y_axis = 500.0;
	camera_speed_z_axis = 7000.0;
	//scroll_speed_factor = 0.0;

	b_zooming_in = false;
	b_zooming_out = false;
}

// Called when the game starts or when spawned
void Amain_map_camera_pawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Amain_map_camera_pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), camera_movement_scale_z_axis, camera_input.Z);                 // DEBUG DISPLAY IN LOG

	// Camera zoom in/out
	if (b_zooming_in == true)
	{
		camera_movement_scale_z_axis = -1.0;
		b_zooming_in = false;
	}
	else if (b_zooming_out == true)
	{
		camera_movement_scale_z_axis = 1.0;
		b_zooming_out = false;
	}
	else
	{
		camera_movement_scale_z_axis = 0.0;
	}

	// Camera final x/y/z axis movement
	camera_movement_x = camera_movement_scale_x_axis * camera_speed_x_axis;
	camera_input.X = camera_movement_x;

	camera_movement_y = camera_movement_scale_y_axis * camera_speed_y_axis;
	camera_input.Y = camera_movement_y;

	camera_movement_z = camera_movement_scale_z_axis * camera_speed_z_axis;
	camera_input.Z = camera_movement_z;

	FVector NewLocation = GetActorLocation();

	NewLocation += GetActorRightVector() * camera_input.X * DeltaTime;
	NewLocation += GetActorForwardVector() * camera_input.Y * DeltaTime;
	NewLocation += GetActorUpVector() * camera_input.Z * DeltaTime;

	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void Amain_map_camera_pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("pan_main_map_camera_pawn_x_axis", this, &Amain_map_camera_pawn::pan_main_map_camera_pawn_x_axis);
	InputComponent->BindAxis("pan_main_map_camera_pawn_y_axis", this, &Amain_map_camera_pawn::pan_main_map_camera_pawn_y_axis);

	InputComponent->BindAction("zoom_in_main_map_camera_pawn", IE_Pressed, this, &Amain_map_camera_pawn::zoom_in_main_map_camera_pawn);
	InputComponent->BindAction("zoom_out_main_map_camera_pawn", IE_Pressed, this, &Amain_map_camera_pawn::zoom_out_main_map_camera_pawn);
}







// Takes input and says which x axis direction the camera is moving and to limit camera speed
void Amain_map_camera_pawn::pan_main_map_camera_pawn_x_axis(float AxisValue)
{
	camera_movement_scale_x_axis = AxisValue;

	if (camera_movement_scale_x_axis > 1) {
		camera_movement_scale_x_axis = 1;
	}
	if (camera_movement_scale_x_axis < -1) {
		camera_movement_scale_x_axis = -1;
	}
}

// Takes input and says which y axis direction the camera is moving
void Amain_map_camera_pawn::pan_main_map_camera_pawn_y_axis(float AxisValue)
{
	camera_movement_scale_y_axis = AxisValue;

	if (camera_movement_scale_y_axis > 1) {
		camera_movement_scale_y_axis = 1;
	}
	if (camera_movement_scale_y_axis < -1) {
		camera_movement_scale_y_axis = -1;
	}
}


// Functions that are used when mouse wheel up or down is pressed
void Amain_map_camera_pawn::zoom_out_main_map_camera_pawn()
{
	b_zooming_out = true;
}
void Amain_map_camera_pawn::zoom_in_main_map_camera_pawn()
{
	b_zooming_in = true;
}