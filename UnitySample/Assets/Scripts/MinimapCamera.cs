using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class MinimapCamera : MonoBehaviour {

    private Camera m_cam = null;
    private Camera cam {
        get
        {
            if(m_cam == null)
            {
                m_cam = GetComponent<Camera>();
            }
            return m_cam;
        }
    }

	// Use this for initialization
	void Start () {
        DungeonGenerator.instance.onEndGenerate.AddListener(() => ResizeCamera());
	}

    private void ResizeCamera()
    {
        float width = DungeonGenerator.instance.Params.width * DungeonGenerator.instance.tileSize;
        float height = DungeonGenerator.instance.Params.height * DungeonGenerator.instance.tileSize;

        transform.position = new Vector3((width - DungeonGenerator.instance.tileSize)/2.0f, 200, (height - DungeonGenerator.instance.tileSize )/ 2.0f);
        cam.orthographicSize = Mathf.Max(width, height) / 2.0f;
    }
}
