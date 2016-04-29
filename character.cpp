//Character

/*
https://wiki.unrealengine.com/First_Person_Shooter_C%2B%2B_Tutorial
http://shootertutorial.com/2015/05/30/configuring-new-project-ue4-main-classes-explanation/
Character is a Pawn but with MovementComponent added. Thanks to that it can use
navigation and move around. Character have SkeletalMeshComponent added as well
so you can assign graphics representation by default.Let’s create new Character
and name it GameplayCharacter.


USEFUL TIP: On Mobile MovementComponent is expensive so if you are doing RTS
game with lot of Characters you should extend from Pawn and implement your own
movement.
https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/ACharacter/index.html
*/


//The Intial FPSCharacter.h
#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AFPSCharacter();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



};
//
//
//
//The Inital FPSCharacter.cpp
#include "FPSProject.h"
#include "FPSCharacter.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AFPSCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

}


/*
* MOVEMENT
These have to be edited in the Project Settings.
Initially toa dd axis mappings
*/

//The Character needs axis movements in the .h file
//handles moving forward/backward

UFUNCTION() // macro*
void MoveForward(float Val);
//handles strafing
UFUNCTION() // macro*
void MoveRight(float Val);

/* The UFUNCTION() Macro

The UFUNCTION macro is used above each of these functions. By itself, the
UFUNCTION macro makes the engine aware of these functions, so that they can be
included in serialization, optimization, and other engine functionality. You may
also have noticed the UCLASS macro above your new FPSGameMode and FPSCharacter
class declarations, which does the same thing but for classes, and there is also
a UPROPERTY macro for properties. There are a number of specifiers you can
supply to these macros to change the function, class, and property behaviors in
the engine, which can be found in ObjectBase.h.
*/

//in the .cpp file
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
    // set up gameplay key bindings
    InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
}
//we do not need to add the UFUNCTION() macros in the .cpp file

//Input components are a component that defines how th handle input data and can be attached to an actor that recieves said input

// Useing the names of the functions we defined in the project settings.
void AFPSCharacter::MoveForward(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling
        if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
        {
            Rotation.Pitch = 0.0f;
        }
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::MoveRight(float Value)
{
    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

//jumping gets down how you think the project settings with all over inputs

void AFPSCharacter::OnStartJump()
{
    bPressedJump = true;
    // this shit just majically works
}
void AFPSCharacter::OnStopJump()
{
    bPressedJump = false;
}

/*
FBX is autodesks propriatary export format
Importing assets involves clicking the green button in the content browser.

Creating a blueprint of the FPSCharacter class allows you to easily change
assets and and change future components.

Add the mesh to the bluepring character class

*/

//replacing earlier code with this

// set default pawn class to our Blueprinted character
static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/BP_FPSCharacter.BP_FPSCharacter_C'"));
if (PlayerPawnObject.Class != NULL)
{
    DefaultPawnClass = PlayerPawnObject.Class;
}
/*
This code will find the class generated by your blueprint and assign it as your
default pawn class. (Note the "_C" suffix in the asset path, this is what
distinguishes the actual class used by the game from the Blueprint asset, which
is an editor-only concept.) At this point, you could also remove the
#include "FPSCharacter.h" from the top of FPSGameMode.cpp, since you are no
longer referring to the FPSCharacter C++ class.
*/

//We must mofify the cunstructor to support what we want.

AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    // Create a CameraComponent
    FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->AttachParent = CapsuleComponent;
    //3. Add this to the constructor, after the component is created. You can tweak the camera's position in the BP_FPSCharacter Blueprint later as well, but this gives a good starting location for the CameraComponent. Also, you will only set the CameraComponent's location, not its rotation, because our earlier Turn and LookUp functions will control the camera's orientation.
    // Position the camera a bit above the eyes
    FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
    // Allow the pawn to control rotation.
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    //this shit didn't work at first...
}

A common FPS approach is to use 2 separate meshes. One is the normal full-body mesh, used when seeing the character from third person but hidden when in first person. The second is a "weapon and hands" mesh that is attached to the camera and is visible only to the player when the player is in a first person perspective.
