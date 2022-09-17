import numpy as np
import matplotlib.pyplot as plt
from pytransform3d.plot_utils import make_3d_axis
from pytransform3d.transform_manager import TransformManager
from scipy.spatial.transform import Rotation

TB2A = np.eye(4)
R = Rotation.from_euler("XYZ",[0,0,0], degrees=True).as_matrix()
TB2A[:3,:3] = R
TB2A[:3,3] = np.array([1,5,3])
TA2B = np.linalg.inv(TB2A)

# Define few points from different frames to frame B
origin_a_in_b = TA2B@np.array([0,0,0,1]).reshape(4,1)

tm = TransformManager()
tm.add_transform("A", "B", TA2B)

plt.figure(figsize=(8, 12))

ax = make_3d_axis(6, 211)
ax = tm.plot_frames_in("B", ax=ax, s=3)
ax.plot(*origin_a_in_b[:3],"rx")
ax.view_init(30, 20)

print(f'{type(ax)}')

plt.show()