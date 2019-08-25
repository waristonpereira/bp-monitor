# Blood Pressure Monitor Lib Algorithm

Based on array of integers and  a point of interest, the algorithm search the greater number before decrement and the less number before increment based on initial point.

![ABP Wave](https://raw.github.com/waristonpereira/bp-monitor/master/doc/abp.png)

### Diagram

### Diagram

### Pseudocode

```
procedure measure ( samples, number of samples, point of interest )
  i ← 0 
  sbp ← 0 
  sbp index ← 0
  for point of interest, number of samples do
    i ← i + 1
    if sample value in i-th position is greater or equal sbp then
      sbp ← sample value in i-th position 
      sbp index ← i
    else
      break
    end if
  end for
  
  i ← 0
  dbp ← 0 
  dbp index ← 0
  for point of interest, zero(0) do
    i ← i - 1
    if sample value in i-th position is less or equal dbp then
      dbp ← sample value in i-th position 
      dbp index ← i
    else
      break
    end if
  end for
  
  return sbp, sbp index, dbp, dbp index
  
end procedure
```