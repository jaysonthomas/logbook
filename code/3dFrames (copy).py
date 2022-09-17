import numpy as np
import matplotlib.pyplot as plt
from pytransform3d.plot_utils import make_3d_axis
from pytransform3d.transform_manager import TransformManager
from scipy.spatial.transform import Rotation

TB2A = np.eye(4)
R = Rotation.from_euler("XYZ",[75,0,-45], degrees=True).as_matrix()
TB2A[:3,:3] = R
TB2A[:3,3] = np.array([1,5,3])
TA2B = np.linalg.inv(TB2A)

TD2A = np.eye(4)
R = Rotation.from_euler("XYZ",[-2,-90,-45], degrees=True).as_matrix()
TD2A[:3,:3] = R
TD2A[:3,3] = np.array([2,-5,2])
TA2D = np.linalg.inv(TD2A)

TC2B = np.eye(4)
R = Rotation.from_euler("XYZ",[45,45,0], degrees=True).as_matrix()
TC2B[:3,:3] = R
TC2B[:3,3] = np.array([1,2,3])
TB2C = np.linalg.inv(TC2B)

# Define few points from different frames to frame A
origin_c_in_a = TB2A@TC2B@np.array([0,0,0,1]).reshape(4,1)
point_P_c_in_a = TB2A @ TC2B @ np.array([2,0,0,1]).reshape(4,1)
origin_d_in_a = TD2A @ np.array([0,0,0,1]).reshape(4,1)

# Define few points from different frames to frame B
origin_a_in_b = TA2B@np.array([0,0,0,1]).reshape(4,1)
origin_c_in_b = TC2B@np.array([0,0,0,1]).reshape(4,1)
origin_d_in_b = TA2B@TD2A@np.array([0,0,0,1]).reshape(4,1)
point_P_c_in_b = TC2B @ np.array([2,0,0,1]).reshape(4,1)

tm = TransformManager()
tm.add_transform("A", "B", TA2B)
tm.add_transform("B","C",TB2C)
tm.add_transform("A", "D", TA2D)

plt.figure(figsize=(8, 12))

ax = make_3d_axis(6, 211)
ax = tm.plot_frames_in("B", ax=ax, s=3)
ax.plot(*origin_a_in_b[:3],"rx")
ax.plot(*origin_c_in_b[:3],"bx")
ax.plot(*origin_d_in_b[:3],"yx")
ax.plot(*point_P_c_in_b[:3],"gx")
ax.view_init(30, 20)

ax = make_3d_axis(6, 212)
ax = tm.plot_frames_in("A", ax=ax,s=3)
ax.plot(*(1,5,3), "yx")
ax.plot(*origin_c_in_a[:3], "rx")
ax.plot(*point_P_c_in_a[:3], "gx")
ax.plot(*origin_d_in_a[:3],"bx")
ax.view_init(30, 20)
plt.show()