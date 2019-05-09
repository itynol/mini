using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    public float speed = 6.0F;

    private Rigidbody rb;
    Vector3 movement;

    RaycastHit hit;
    Ray newray;

    int layerMask;

    float rotationY = 0f;

    public float sensitivityY = 15f;
    public float minimumY = -360f;
    public float maximumY = 360f;

    void Start()
    {
        layerMask = 1 << 8;
        Cursor.lockState = CursorLockMode.Locked;
        rb = GetComponent<Rigidbody>();
    }

    void Update()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        rotationY += Input.GetAxis("Mouse X") * sensitivityY;
        transform.localEulerAngles = new Vector3(0, rotationY, 0);
        Debug.DrawRay(transform.position, transform.forward * 40F);
        movement = (moveHorizontal * transform.right + moveVertical * transform.forward).normalized;
        if (Input.GetKey(KeyCode.Mouse0))
        {
            newray = new Ray(transform.position, transform.forward);
            if (Physics.Raycast(newray, out hit, 40F))
                Debug.Log("1");

        }
    }

    void FixedUpdate()
    {
        Move();
        //transform.Rotate(0, rotationY , 0);
    }

    void Move()
    {
        rb.velocity = movement * speed * Time.deltaTime;
    }
}