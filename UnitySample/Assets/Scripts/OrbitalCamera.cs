using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class OrbitalCamera : MonoBehaviour {
    enum UpdateMode
    {
        Update,
        LateUpdate,
        FixedUpdate
    }

    [SerializeField] Transform target;
    [SerializeField] Vector3 lookingOffset;
    [SerializeField] bool shouldCollide = true;
    [SerializeField] float collisionRadius = 0.4f;
    [SerializeField] UpdateMode mode = UpdateMode.Update;
    [SerializeField] bool freeFly = true;
    [Header("Rotation")]
    [SerializeField] float mouseSensitivity = 1.0f;
    [SerializeField] float maxAngleUp = 85;
    [SerializeField] float maxAngleDown = 85;
    [SerializeField] bool smoothRotation = false;
    [SerializeField] float rotationDamp = 0.2f;
    [SerializeField] Vector2 startAngle = Vector2.zero;
    [Header("Zoom")]
    [SerializeField] float scrollSpeed = 0.5f;
    [SerializeField] float distanceMin = 5.0f;
    [SerializeField] float distanceMax = 5.0f;
    [SerializeField] float startDistance = 5.0f;
    [SerializeField] bool smoothZoom = true;
    [SerializeField] float zoomDamp = 0.2f;

    Quaternion rotation;
    Vector3 position;
    float distanceTarget;
    float distanceCurrent;
    float distanceSpeed = 0.0f;

    float angleXCurrent;
    float angleXTarget;
    float angleXSpeed = 0.0f;


    float angleYCurrent;
    float angleYTarget;
    float angleYSpeed = 0.0f;

    protected float deltaX = 0.0f;
    protected float deltaY = 0.0f;

    // Use this for initialization
    protected virtual void Start ()
    {
        rotation = Quaternion.identity;
        position = Vector3.zero;
        distanceTarget = startDistance;
        distanceCurrent = distanceTarget;
        angleXTarget = startAngle.x;
        angleXCurrent = angleXTarget;
        angleYTarget = startAngle.y;
        angleYCurrent = angleYTarget;
    }

    private void Update()
    {
        if(mode == UpdateMode.Update)
        {
            UpdateCamera();
        }
    }

    // Update is called once per frame
    private void LateUpdate()
    {
        if (mode == UpdateMode.LateUpdate)
        {
            UpdateCamera();
        }
    }

    private void FixedUpdate()
    {
        if (mode == UpdateMode.FixedUpdate)
        {
            UpdateCamera();
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawWireSphere(transform.position, collisionRadius);
    }

    protected virtual void UpdateInputs()
    {
        if (Input.GetMouseButton(1) && !EventSystem.current.IsPointerOverGameObject())
        {
            deltaX = Input.GetAxis("Mouse Y");
            deltaY = Input.GetAxis("Mouse X");
        }
        else
        {
            deltaX = 0.0f;
            deltaY = 0.0f;
        }
    }

    private void UpdateCamera ()
    {
        Vector3 lookPosition = target.position + lookingOffset;

        UpdateInputs();

        if(freeFly && deltaX == 0 && deltaY == 0)
        {
            // Camera free fly (more natural with player movement)
            Quaternion rot = Quaternion.identity;
            Vector3 dirPrev = Vector3.Scale(rotation * Vector3.forward, new Vector3(1, 0, 1)).normalized;
            Vector3 dirNew = Vector3.Scale(lookPosition - transform.position, new Vector3(1, 0, 1)).normalized;
            rot.SetFromToRotation(dirPrev, dirNew);

            angleYTarget += rot.eulerAngles.y;
        }
        else
        {
            angleXTarget = angleXTarget - mouseSensitivity * deltaX;
            angleYTarget = angleYTarget + mouseSensitivity * deltaY;

            // Clamp to avoid gimbal lock
            maxAngleUp = Mathf.Clamp(maxAngleUp, 0, 89.999f);
            maxAngleDown = Mathf.Clamp(maxAngleDown, 0, 89.999f);

            if (angleXTarget > maxAngleUp) angleXTarget = maxAngleUp;
            if (angleXTarget < -maxAngleDown) angleXTarget = -maxAngleDown;

        }

        if (smoothRotation)
        {
            angleXCurrent = Mathf.SmoothDampAngle(angleXCurrent, angleXTarget, ref angleXSpeed, rotationDamp);
            angleYCurrent = Mathf.SmoothDampAngle(angleYCurrent, angleYTarget, ref angleYSpeed, rotationDamp);
        }
        else
        {
            angleXCurrent = angleXTarget;
            angleYCurrent = angleYTarget;
        }

        rotation.eulerAngles = new Vector3(angleXCurrent, angleYCurrent, rotation.eulerAngles.z);


        Vector3 lookDirection = rotation * Vector3.forward;

        // Zoom
        distanceTarget -= scrollSpeed * Input.mouseScrollDelta.y * (!EventSystem.current.IsPointerOverGameObject() ? 1 : 0);
        distanceTarget = Mathf.Clamp(distanceTarget, distanceMin, distanceMax);
        if(smoothZoom)
        {
            distanceCurrent = Mathf.SmoothDamp(distanceCurrent, distanceTarget, ref distanceSpeed, zoomDamp);
        }
        else
        {
            distanceCurrent = distanceTarget;
        }

        RaycastHit hit;
        if (shouldCollide && Physics.SphereCast(lookPosition, collisionRadius, -lookDirection, out hit, distanceCurrent, -1, QueryTriggerInteraction.Ignore))
        {
            position = lookPosition - lookDirection * ((hit.point + hit.normal * collisionRadius) - lookPosition).magnitude;
        }
        else
        {
            position = lookPosition - lookDirection * distanceCurrent;
        }

        transform.position = position;
        transform.rotation = rotation;
    }
}
