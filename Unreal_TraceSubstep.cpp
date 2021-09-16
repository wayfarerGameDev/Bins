//////////////////
///.h

USTRUCT(BlueprintType)
struct FHitTask
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite)
        USceneComponent* SceneComponentTransformToTrack;
    UPROPERTY(BlueprintReadWrite)
        EFluidCharacterHitTaskShape Shape;
    UPROPERTY(BlueprintReadWrite)
        FVector Extent;
    UPROPERTY(BlueprintReadWrite)
        int SubSteps;
    FVector LocationAtLastFrame;
    FRotator RotationAtLastFrame;
};

//////////////////
///.cpp

static TAutoConsoleVariable<int32> CVarHitTraceDubug(
    TEXT("Hit.Trace.Debug"),
    0,
    TEXT("Turns hit trace debugging.\n")
    TEXT("<=0: off \n")
    TEXT("  1: on\n"),
    ECVF_SetByConsole);


void UHitSubsystem::Tick(float DeltaTime)
{
    
    //Trace Variables
    TArray<AActor*> ActorsToIgnoire;
    TArray<FHitResult> HitArray;
    bool bDidHit = false;
    
    //Frame Variables
    FVector FrameLocation = FVector(0,0,0);
    FRotator FrameRotation;
    
    //Substep Variables
    FVector SubStepLocation = FVector(0,0,0);
    FRotator SubStepRotation;
    float SubStepAlpha = 0;
    
    //Do Hit Tasks
    for (int i = 0; i < HitTasks.Num(); i ++)
    {
        //Set StartEnd
        FrameLocation = HitTasks[i].SceneComponentTransformToTrack->GetComponentLocation();
        FrameRotation = HitTasks[i].SceneComponentTransformToTrack->GetComponentRotation();
        
        // Do Substeps
        for (float j = 0; j < HitTasks[i].SubSteps && j < 12; j++)
        {
            //Substep
            SubStepAlpha = j / HitTasks[i].SubSteps;
            SubStepLocation = FMath::LerpStable(HitTasks[i].LocationAtLastFrame, FrameLocation, SubStepAlpha);
            SubStepRotation = FMath::LerpStable(HitTasks[i].RotationAtLastFrame, FrameRotation, SubStepAlpha);
            
            //Box Trace
            bDidHit = UKismetSystemLibrary::BoxTraceMulti(GetWorld(),SubStepLocation, SubStepLocation, HitTasks[i].Extent,FrameRotation, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnoire,CVarHitTraceDubug.GetValueOnAnyThread() > 0 ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitArray, false, FLinearColor::Red, FLinearColor::Red, 1);
        }
        
        //Set
        HitTasks[i].LocationAtLastFrame = FrameLocation;
        HitTasks[i].RotationAtLastFrame = FrameRotation;
    }
}
