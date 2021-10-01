//This Is A Example On How To Get Yaw And Delta Yaw (For player to move realtive to camera)
//


void ExampleClass::GetYawAndDeltaYaw(const float ActorYaw,const float CameraYaw, const float X, const float Y, const bool bIsPlayerControlled, float& YawDelta_out, float& YawDelta_out)
{
     //Angle From Radians As Tangent Of Angle Of XY (Atan2) Convert It To Degrees
     float InputYaw = FMath::RadiansToDegrees(FMath::Atan2(X,Y));

     //Delta Yaw | Yaw Based On Player (Camera)
     if (bIsPlayerControlled)
     {
          //Set Yaw To Camera Yaw To Start With | Get Delta Way Based On Camera Yaw
          Yaw_out = CameraYaw;
          YawDelta_out = MathAngleDelta(CameraYaw,ActorYaw);
      }
    
      //Add Input Yaw To Yaw | Get Delta Yaw Based On Input
      Yaw_out += InputYaw;
      YawDelta_out = MathAngleDelta(YawDelta_out,InputYaw);
}

float ExampleClass::MathAngleDelta(const float StartAngle, const float EndAngle)
{
    float Delta = EndAngle - StartAngle;
    if (Delta > 180.0)
        Delta -= 360.0f;
    else if (Delta < -180.0f)
        Delta += 360.0f;

    return Delta;
}
