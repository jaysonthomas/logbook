#include <iostream>
#include <vector>

u_int32_t TrappedWater(const std::vector<u_int16_t> &towerHeights) 
{
  if (towerHeights.size() < 3)
    return 0;

  u_int16_t leftIndex = 0;
  u_int16_t rightIndex = towerHeights.size() - 1;

  u_int16_t leftMaxHeight = 0;
  u_int16_t rightMaxHeight = 0;

  u_int32_t runningSum = 0;

  while (leftIndex < rightIndex)
  {
    if (towerHeights[leftIndex] < towerHeights[rightIndex])
    {
      if (towerHeights[leftIndex] >= leftMaxHeight)
        leftMaxHeight = towerHeights[leftIndex];
      else
        runningSum += leftMaxHeight - towerHeights[leftIndex];

      leftIndex++;
    }
    else
    {
      if (towerHeights[rightIndex] >= rightMaxHeight)
        rightMaxHeight = towerHeights[rightIndex];
      else
        runningSum += rightMaxHeight - towerHeights[rightIndex];

      rightIndex--;
    }
  }

  return runningSum;
}

void Test(const u_int16_t &test, const std::vector<u_int16_t> &heights,
          const u_int32_t &expected) 
{
  const u_int32_t result = TrappedWater(heights);

  if (result == expected)
    std::cout << "Passed test "<< test <<".\n";
  else
    std::cout << "FAIL: test "<< test <<": expected " << expected << " but got " << result << ".\n";
}

int main() {
  Test(1, {1, 0, 1}, 1);
  Test(2, {0, 3, 0, 0, 2}, 4);
  Test(3, {0, 3, 2, 5, 4, 2, 1, 0, 5, 0, 5, 4, 1}, 19);
  Test(4, {0, 2, 3, 2, 3, 5, 3, 2, 3, 2, 4, 0, 5, 7, 1}, 17);
  Test(5, {65535, 0, 0, 65535}, 131070);

	return 0;
}