This algorithm solves the coloring problem by creating a quota, a list containing the number of Nodes that need to be colored for each color. 
The whole quota is created by giving the first color a value of one, and giving every other color a value of floor(((2^n) - 2) / (n - 1)). 
If any amount is leftover, increment each color from 2 to the nth color, but only incrementing the second and third color if the calculated value is even. 
Given the number of levels of a full binary tree, n. 
The list is traversed looking for a 1 in the quota and coloring the root in that color. 
From there, if the root has children, divide the root quota between the two children.
Dividing the root quota is done by finding an acceptable root for the left tree and using the same process to find a suitable root for right subtree. 
After suitable roots are found, divide the remaining nodes between each subtree.
Once subtrees have filled quotas, verify that the quotas are correct by checking if the total Nodes in the left and right subtree quotas are equal, 
    the total for each color equals the total Nodes in the root quota and that no value in the sub-quotas is larger than the lowest level.
If this is incorrect then decrement a non-root value from the larger quota and increment the same value from the smaller quota until either the maximum 
    possible is reached on the smaller side or until the two quotas hold the same number of nodes. If the maximum value is reached and imbalance still exists, 
    then find the next non-root value and repeat the process.
Once both subtrees have correct quotas, repeat from step 1 for the left child and the right child.
		
1 Determining a proper root is done by going through the quotas of the child and root and looking for a value that has not been assigned in the child’s quota that has a remainder that can fit in his brother’s tree. Which is determined by comparing the total minus one if it is less than or equal to 2^(level - 1)
2 Division is done through by dividing the parent quota value by 2 and putting the remainder into the other child’s quota. Then alternating between children and doing this process until all colors are assigned.
