import time
from numba import njit
from numba import prange
import numpy as np
import numpy.lib.stride_tricks
import cv2
from cProfile import Profile
from pstats import SortKey, Stats
import multiprocessing.pool

# important!! - for very large operations (like s > 15 or even 20) parallel = True improves the calcs by a lot
@njit(fastmath=True)
def func(img: np.ndarray, blockSize: tuple[int, int], thresh):
    blocked = numpy.lib.stride_tricks.sliding_window_view(img, blockSize)
    new = np.zeros((blocked.shape[0], blocked.shape[1]), np.uint8)
    for i in prange(len(blocked)):
        for j in prange(len(blocked[0])):
            if np.sum(blocked[i][j]) > thresh:
                new[i][j] = 255
    return new

def last():    
    v = cv2.VideoCapture("/home/sagi21805/waterlo23.mp4")
    s = 2
    thresh = 100*s*s
    while True:
        suc, img = v.read()  
        img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        img = cv2.resize(img, (1280, 720))
        st = time.time()
        new = func(img, (3, 3), thresh)
        print(1 / (time.time() - st))
        cv2.imshow("!", new)
        cv2.waitKey(1)

last()