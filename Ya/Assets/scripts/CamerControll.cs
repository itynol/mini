using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CamerControll : MonoBehaviour
{
    public float minimumX;
    public float maximumX;

    public float sensitivityX;


    public Camera cam;

    float rotationX = 0f;
    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {
        rotationX += Input.GetAxis("Mouse Y") * sensitivityX;
        rotationX = Mathf.Clamp(rotationX, minimumX, maximumX);

        cam.transform.localEulerAngles = new Vector3(-rotationX, 0, 0);

        if (Input.GetKey(KeyCode.Escape))
        {
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
        }
        if (Input.GetKey(KeyCode.Mouse0))
        {
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
        }

    }
}
