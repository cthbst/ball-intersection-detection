from checkCollisions import checkCollisions
import random

def testRandom2dBalls():
    # test 5 times
    for t in range(5):
        balls = [[
            random.uniform(0, 10),
            random.uniform(0, 10),
            random.uniform(0, 3)
        ] for _ in range(100)]

        r_fast = checkCollisions(balls)
        r_slow = []
        for j in range(len(balls)):
            for i in range(j):
                dx = balls[i][0] - balls[j][0]
                dy = balls[i][1] - balls[j][1]
                R = balls[i][2] + balls[j][2]
                if dx**2 + dy**2 <= R**2:
                    r_slow.append((i, j))
        assert sorted(r_slow) == sorted(r_fast)

def test1D():
    # intersect
    r = checkCollisions([[0, 6], [10, 6]])
    assert sorted(r) == [(0, 1)]

    # tangent
    r = checkCollisions([[0, 4], [10, 6]])
    assert sorted(r) == [(0, 1)]

    # no intersect
    r = checkCollisions([[0, 4], [10, 4]])
    assert sorted(r) == []

    # multiple balls
    r = checkCollisions([[0, 6], [10, 6], [20, 6]])
    assert sorted(r) == [(0, 1), (1, 2)]

def test2D():
    # intersect
    r = checkCollisions([[0, 0, 8], [10, 10, 8]])
    assert sorted(r) == [(0, 1)]

    # tangent
    r = checkCollisions([[0, 0, 2], [3, 4, 3]])
    assert sorted(r) == [(0, 1)]

    # no intersect
    r = checkCollisions([[0, 0, 4], [10, 10, 4]])
    assert sorted(r) == []

    # multiple balls
    r = checkCollisions([[0, 5, 6], [10, 5, 6], [20, 5, 6]])
    assert sorted(r) == [(0, 1), (1, 2)]
