void UFluidCharacterHitSubsystem::Tick(float DeltaTime)
{
    
    //Trace Variables
    TArray<AActor*> ActorsToIgnoire;
    TArray<FHitResult> HitArray;
    bool bDidHit = false;
    
    //Frame Variables
    FVector FrameLocation = FVector(0,0,0);
    FRotator FrameOrientation;
    
    //Substep Variables
    FVector SubStepLocation = FVector(0,0,0);
    float SubStepAlpha = 0;
    
    //Do Hit Tasks
    for (int i = 0; i < HitTasks.Num(); i ++)
    {
        //Set StartEnd
        FrameLocation = HitTasks[i].SceneComponentTransformToTrack->GetComponentLocation();
        FrameOrientation = HitTasks[i].SceneComponentTransformToTrack->GetComponentRotation();
        
        // Do Substeps
        for (int j = 0; j < HitTasks[i].SubSteps; j++)
        {
            //Substep
            SubStepAlpha = DeltaTime / HitTasks[i].SubSteps * j;
            SubStepLocation = FMath::LerpStable(HitTasks[i].LocationAtLastFrame, FrameLocation, SubStepAlpha);

            //Box Trace
            if (HitTasks[i].Shape == EFluidCharacterHitTaskShape::VE_Box)
                bDidHit = UKismetSystemLibrary::BoxTraceMulti(GetWorld(),SubStepLocation, SubStepLocation, HitTasks[i].Extent,FrameOrientation, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnoire,       CVarFluidCharacterHitTraceDubug.GetValueOnAnyThread() > 0 ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitArray, false, FLinearColor::Red, FLinearColor::Red, 1);
        }
        
        //Set
        HitTasks[i].LocationAtLastFrame = FrameLocation ;
    }
}
