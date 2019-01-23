using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class CameraTarget : MonoBehaviour
{
    [SerializeField] new Camera camera;
    [SerializeField] float speed = 1.0f;
    [SerializeField] float mouseSpeed = 1.0f;

    Vector3 targetDirection = Vector3.zero;
    Vector3 currentDirection = Vector3.zero;
    Vector3 speedDirection = Vector3.zero;
    float dampDirection = 0.1f;

    // Update is called once per frame
    void Update()
    {
        Vector3 forward = Vector3.Scale(new Vector3(1, 0, 1), camera.transform.forward).normalized;
        Vector3 right = Vector3.Cross(Vector3.up, forward);
        targetDirection = Vector3.zero;

        if(Input.GetMouseButton(0) && !EventSystem.current.IsPointerOverGameObject())
        {
            targetDirection = -(right * Input.GetAxisRaw("Mouse X") + forward * Input.GetAxisRaw("Mouse Y")) * mouseSpeed;
        }
        else
        {
            targetDirection = speed * (right * Input.GetAxisRaw("Horizontal") + forward * Input.GetAxisRaw("Vertical")).normalized;
        }

        currentDirection = Vector3.SmoothDamp(currentDirection, targetDirection, ref speedDirection, dampDirection);
        transform.position += currentDirection * Time.deltaTime;
    }
}
