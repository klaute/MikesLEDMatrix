/*Klaute möchte das ganze mathematisch gelöst haben.
  Dann mach ich das so :) */

#include "blockeq.h"

void blockEqualizerBold(uchar* blockValue, bool on)
{
	uchar i = 0;
	uchar leftShiftValue;
	uchar tmp;

	if(falldown == 1)
		falldown = 0;
	else
		falldown = 1;

	

	//BlockBold 0
	if(blockValue[i] == 0)
	{
		cube[7][5] = 0;
		cube[7][4] = 0;
		cube[6][7] = 0;
		cube[6][6] = 0;
		cube[6][3] = 0;
		cube[6][2] = 0;
	}
	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
		/*wir brauchen von den byte nur die ersten 4 bits
		  00001111
		  die werden je nach wert nach links verschoben
		  00111100
		  aber wir wollen immer noch nur die ersten 4 bits
		    00111100
		  & 00001111
		  ----------
		    00001100 */

                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[7][5] = tmp;
		cube[7][4] = tmp;
		cube[6][7] = 0;
		cube[6][6] = 0;
		cube[6][3] = 0;
		cube[6][2] = 0;
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[7][5] = 15;
		cube[7][4] = 15;
		cube[6][7] = 255 << leftShiftValue;
		cube[6][6] = 255 << leftShiftValue;
		cube[6][3] = 0;
		cube[6][2] = 0;
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[7][5] = 15;
		cube[7][4] = 15;
		cube[6][7] = 255;
		cube[6][6] = 255;
		cube[6][3] = 240 << leftShiftValue;
		cube[6][2] = 240 << leftShiftValue;
	}  
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	
	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[7][5] |= tmp;
		cube[7][4] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[6][7] |= tmp;
		cube[6][6] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[6][3] |= tmp;
		cube[6][2] |= tmp;
	}
   	}
	//BlockBold 1
    	i = 1;
	if(blockValue[i] == 0)
	{
		cube[7][2] = 0;
		cube[5][7] = 0;
		cube[6][4] = 0;
		cube[4][7] = 0;
		cube[6][0] = 0; 
		cube[3][7] = 0;
	}

	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[7][2] = tmp;
		cube[5][7] = tmp;
		cube[6][4] = 0;
		cube[4][7] = 0;
		cube[6][0] = 0; 
		cube[3][7] = 0;		
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[7][2] = 15;
		cube[5][7] = 15;
		cube[6][4] = 255 << leftShiftValue;
		cube[4][7] = 255 << leftShiftValue;
		cube[6][0] = 0; 
		cube[3][7] = 0;
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[7][2] = 15;
		cube[5][7] = 15;
		cube[6][4] = 255;
		cube[4][7] = 255;
		cube[6][0] = 240 << leftShiftValue;
		cube[3][7] = 240 << leftShiftValue;
	}
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	
  
	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[7][2] |= tmp;
		cube[5][7] |= tmp;
	}

	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[6][4] |= tmp;
		cube[4][7] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[6][0] |= tmp;
		cube[3][7] |= tmp;
	}
	}
	//BlockBold 2
    	i = 2;
	if(blockValue[i] == 0)
	{
		cube[5][5] = 0;
		cube[5][4] = 0;
		cube[4][5] = 0;
		cube[4][4] = 0;
		cube[3][5] = 0;
		cube[3][4] = 0;
	}

	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[5][5] = tmp;
		cube[5][4] = tmp;
		cube[4][5] = 0;
		cube[4][4] = 0;
		cube[3][5] = 0;
		cube[3][4] = 0;		
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[5][5] = 15;
		cube[5][4] = 15;
		cube[4][5] = 255 << leftShiftValue;
		cube[4][4] = 255 << leftShiftValue;
		cube[3][5] = 0;
		cube[3][4] = 0;	
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[5][5] = 15;
		cube[5][4] = 15;
		cube[4][5] = 255;
		cube[4][4] = 255;
		cube[3][5] = 240 << leftShiftValue;
		cube[3][4] = 240 << leftShiftValue;
	}  
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	
	
	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[5][5] |= tmp;
		cube[5][4] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[4][5] |= tmp;
		cube[4][4] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[3][5] |= tmp;
		cube[3][4] |= tmp;
	}
	}
	//BlockBold 3
    	i = 3;
	if(blockValue[i] == 0)
	{
		cube[5][2] = 0;
		cube[5][1] = 0;
		cube[4][2] = 0;
		cube[4][1] = 0;
		cube[3][2] = 0;
		cube[3][1] = 0;
	}

	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[5][2] = tmp;
		cube[5][1] = tmp;
		cube[4][2] = 0;
		cube[4][1] = 0;
		cube[3][2] = 0;
		cube[3][1] = 0;		
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[5][2] = 15;
		cube[5][1] = 15;
		cube[4][2] = 255 << leftShiftValue;
		cube[4][1] = 255 << leftShiftValue;
		cube[3][2] = 0;
		cube[3][1] = 0;	
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[5][2] = 15;
		cube[5][1] = 15;
		cube[4][2] = 255;
		cube[4][1] = 255;
		cube[3][2] = 240 << leftShiftValue;
		cube[3][1] = 240 << leftShiftValue;
	}  
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	

	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[5][2] |= tmp;
		cube[5][1] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[4][2] |= tmp;
		cube[4][1] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[3][2] |= tmp;
		cube[3][1] |= tmp;
	}
	}
	//BlockBold 4
    	i = 4;
	if(blockValue[i] == 0)
	{
		cube[2][7] = 0;
		cube[2][6] = 0;
		cube[1][7] = 0;
		cube[1][6] = 0;
		cube[0][7] = 0;
		cube[0][6] = 0;
	}
	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[2][7] = tmp;
		cube[2][6] = tmp;
		cube[1][7] = 0;
		cube[1][6] = 0;
		cube[0][7] = 0;
		cube[0][6] = 0;		
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[2][7] = 15;
		cube[2][6] = 15;
		cube[1][7] = 255 << leftShiftValue;
		cube[1][6] = 255 << leftShiftValue;
		cube[0][7] = 0;
		cube[0][6] = 0;		
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[2][7] = 15;
		cube[2][6] = 15;
		cube[1][7] = 255;
		cube[1][6] = 255;
		cube[0][7] = 240 << leftShiftValue;
		cube[0][6] = 240 << leftShiftValue;
	}  
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	
	
	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[2][7] |= tmp;
		cube[2][6] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[1][7] |= tmp;
		cube[1][6] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[0][7] |= tmp;
		cube[0][6] |= tmp;
	}
	}
	//BlockBold 5
    	i = 5;
	if(blockValue[i] == 0)
	{
                cube[2][4] = 0;
		cube[2][3] = 0;
		cube[1][4] = 0;
		cube[1][3] = 0;
		cube[0][4] = 0;
		cube[0][3] = 0;
	}
	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[2][4] = tmp;
		cube[2][3] = tmp;		
		cube[1][4] = 0;
		cube[1][3] = 0;
		cube[0][4] = 0;
		cube[0][3] = 0;
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[2][4] = 15;
		cube[2][3] = 15;
		cube[1][4] = 255 << leftShiftValue;
		cube[1][3] = 255 << leftShiftValue;
		cube[0][4] = 0;
		cube[0][3] = 0;	
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[2][4] = 15;
		cube[2][3] = 15;
		cube[1][4] = 255;
		cube[1][3] = 255;
		cube[0][4] = 240 << leftShiftValue;
		cube[0][3] = 240 << leftShiftValue;
	} 
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	

	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[2][4] |= tmp;
		cube[2][3] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[1][4] |= tmp;
		cube[1][3] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[0][4] |= tmp;
		cube[0][3] |= tmp;
	}
	}
	//BlockBold 6
    	i = 6;
	if(blockValue[i] == 0)
	{
                cube[2][1] = 0;
		cube[2][0] = 0;
		cube[1][1] = 0;
		cube[1][0] = 0;
		cube[0][1] = 0;
		cube[0][0] = 0;
	}

	if(blockValue[i] > 0 && blockValue[i] < 5)
	{
		leftShiftValue = 4 - blockValue[i];
                tmp = 15 << leftShiftValue;
		tmp &= 15;
		cube[2][1] = tmp;
		cube[2][0] = tmp;		
		cube[1][1] = 0;
		cube[1][0] = 0;
		cube[0][1] = 0;
		cube[0][0] = 0;
	}
	
	if(blockValue[i] > 4 && blockValue[i] < 13)
	{
		leftShiftValue = 8 - (blockValue[i] - 4);
                cube[2][1] = 15;
		cube[2][0] = 15;
		cube[1][1] = 255 << leftShiftValue;
		cube[1][0] = 255 << leftShiftValue;
		cube[0][1] = 0;
		cube[0][0] = 0;
	}  

	if(blockValue[i] > 12 && blockValue[i] < 17)
	{
		leftShiftValue = 4 - (blockValue[i] - 12);
                cube[2][1] = 15;
		cube[2][0] = 15;
		cube[1][1] = 255;
		cube[1][0] = 255;
		cube[0][1] = 240 << leftShiftValue;
		cube[0][0] = 240 << leftShiftValue;
	}
	if(falldown == 1 && on == true)
	{
		if(qBlock[i] <= blockValue[i] + 2)
			qBlock[i] = blockValue[i] + 2;
		if(qBlock[i] > blockValue[i] + 2)
			qBlock[i]--;
	

	if(qBlock[i] > 0 && qBlock[i] < 5)
	{
		leftShiftValue = 4 - qBlock[i];
        	tmp = 1 << leftShiftValue;
		
		cube[2][1] |= tmp;
		cube[2][0] |= tmp;
	}
	if(qBlock[i] > 4 && qBlock[i] < 13)
	{
		leftShiftValue = 8 - (qBlock[i] - 4);
        	tmp = 1 << leftShiftValue;
		
		cube[1][1] |= tmp;
		cube[1][0] |= tmp;
	}
	if(qBlock[i] > 12 && qBlock[i] < 19)
	{
		leftShiftValue = 6 - (qBlock[i] - 12);
        	tmp = 4 << leftShiftValue;
		
		cube[0][1] |= tmp;
		cube[0][0] |= tmp;
	}
   	}
}


