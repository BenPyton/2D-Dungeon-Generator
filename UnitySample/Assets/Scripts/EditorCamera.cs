using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EditorCamera : OrbitalCamera
{
    protected override void Start()
    {
        base.Start();
        Cursor.lockState = CursorLockMode.None;
    }

    protected override void UpdateInputs()
    {
        if(Input.GetMouseButton(1))
        {
            base.UpdateInputs();
        }
        else
        {
            deltaX = 0.0f;
            deltaY = 0.0f;
        }
    }

}
