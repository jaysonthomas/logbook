#include <iostream>
#include <vector>

u_int16_t getPIndexOfNextHighestPeak(const std::vector<u_int16_t>& towerHeights,
                               const u_int16_t& currentPIndex, 
                               const std::vector<u_int16_t>& tpIndex)
{
  u_int16_t nextHighestPeak = 0;
  u_int16_t nextHighestPIndex = 0;

  for (std::size_t j=currentPIndex+1; j<tpIndex.size(); j++)
  {
    if (towerHeights[tpIndex[j]] >= towerHeights[tpIndex[currentPIndex]])
    {
      return j;
    }
    
    if (towerHeights[tpIndex[j]] > nextHighestPeak)
    {
      nextHighestPIndex = j;
      nextHighestPeak = towerHeights[tpIndex[nextHighestPIndex]];
    }
  }
  return nextHighestPIndex;
}

std::vector<u_int16_t> getTowerPeakIndices(const std::vector<u_int16_t> &towerHeights)
{
  std::vector<u_int16_t> peaks;
  u_int16_t prevHeight = 0;
  int32_t prevSlope = 0;

  for (std::size_t i=0; i<towerHeights.size(); i++)
  {  
    const int32_t slope = towerHeights[i] - prevHeight; 
    if (slope < 0 && prevSlope >= 0)
    {
      peaks.push_back(i-1);
    }
    else if (slope > 0 && i == towerHeights.size()-1)
    {
      peaks.push_back(i);
    }
    
    prevSlope = slope;
    prevHeight = towerHeights[i];
  }
  return peaks;
}

u_int32_t getTrappedWaterBetweenPeaks(const std::vector<u_int16_t> &towerHeights,
                                const std::vector<u_int16_t> tpIndex,
                                const u_int16_t currentPIndex,
                                const u_int16_t nextHighestPIndex)
{
  const u_int16_t currentTPIndex = tpIndex[currentPIndex];
  const u_int16_t nextHighestTPIndex = tpIndex[nextHighestPIndex];
  
  const u_int16_t minPeak = (towerHeights[nextHighestTPIndex] < towerHeights[currentTPIndex]) ? towerHeights[nextHighestTPIndex] : towerHeights[currentTPIndex];

  u_int32_t trappedWater = 0;
  for (std::size_t j=currentTPIndex+1; j<nextHighestTPIndex; j++)
  {
    trappedWater += minPeak - towerHeights[j];
  }
  return trappedWater;
}

u_int32_t TrappedWater(const std::vector<u_int16_t> &towerHeights) 
{
  // tpIndex holds indices of all the peaks in the main array, towerHeights.
  // pIndex refers to the indices of tpIndex.
  const std::vector<u_int16_t> tpIndex = getTowerPeakIndices(towerHeights);
  u_int16_t nextHighestPIndex = 0;

  u_int32_t runningSum = 0;
  for (std::size_t i=0; i<tpIndex.size()-1; i=nextHighestPIndex)
	{
    nextHighestPIndex = getPIndexOfNextHighestPeak(towerHeights, i, tpIndex);
    runningSum += getTrappedWaterBetweenPeaks(towerHeights, tpIndex, i, nextHighestPIndex);    
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
