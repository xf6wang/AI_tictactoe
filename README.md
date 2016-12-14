# tic-tac-toe
Play tic tac toe against a computer AI

Logic for computer AI is as follows:  
1. Can I win? Attempt to see if the I can win this move, if so, take it  
2. Can you win? If you can win in the next move, block it  
3. Attack. Setup this move such that next move I can win  
4. Claim middle. Attempt to claim spots near middle if no other move  

This simple chain of evaluation results in an unbeatable CPU. It's not that fun to play a machine that can't lose, but it's kinda cool.
