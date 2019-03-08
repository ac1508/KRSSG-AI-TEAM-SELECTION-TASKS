#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

enum lift { stop=-1 , up1=1 ,down1=2};

enum floor { none=0 , up=1 , down=2 , bothupdown=3 , internal=4 , upandinternal=5 , downandinternal=6 , updownandinternal=7};
enum floor *floor_state;

int a[100];
int *b[100];
int j=0;
int k=0;

void up_to_none(int);
void down_to_none(int);
void bothupdown_to_up(int);
void bothupdown_to_down(int);
void internal_to_none(int);
void upandinternal_to_up(int);
void upandinternal_to_none(int);
void downandinternal_to_down(int);
void downandinternal_to_none(int);
void updownandinternal_to_up(int);
void updownandinternal_to_down(int);

void stop_to_up();
void stop_to_down();
void up_to_stop();
void down_to_stop();
void up_to_down();
void down_to_up();

int traverse(int index , enum lift lift_state);

int n,high,low;

int main()
{
	int i,temp,index,l,m,diff,sum=0,low1=100;
	char temp_s[15];
	int *c,*d;	
	printf("Enter no. of floors in the building:\n");
	scanf("%d", &n);
	floor_state=(enum floor *)calloc(n, sizeof(enum floor));
	for(i=0;i<n;i++)
		floor_state[i]=none;
	printf("Enter sequence of buttons pressed from within the lift:(-1 to stop)\n");
	for(i=0;i<n;i++)
	{
		scanf("%d", &temp);
		if(temp == -1)
			break;
		else
			floor_state[temp] = internal;
	}
	printf("Enter floor button pressed outside and the mode in the next line:(-1 to stop)\n");
	for(i=0;i<n;i++)
	{
		scanf("%d", &temp);
		if(temp == -1)
			break;
		scanf("%s", temp_s);
		if(strcmp(temp_s,"up") == 0 && floor_state[temp] == internal)
			floor_state[temp] = upandinternal;
		else if(strcmp(temp_s,"up") == 0 && floor_state[temp] == none)
			floor_state[temp] = up;
		else if(strcmp(temp_s,"down") == 0 && floor_state[temp] == internal)
			floor_state[temp] = downandinternal;
		else if(strcmp(temp_s,"down") == 0 && floor_state[temp] == none)
			floor_state[temp] = down;
		else if(strcmp(temp_s,"bothupdown") == 0 && floor_state[temp] == internal)
			floor_state[temp] = updownandinternal;
		else if(strcmp(temp_s,"bothupdown") == 0 && floor_state[temp] == none)
			floor_state[temp] = bothupdown;
	}
	for(i=0;i<n;i++)
		if(floor_state[i] != none)
			high=i;
	for(i=n-1;i>=0;i--)
		if(floor_state[i] != none)
			low=i;
	printf("Please enter which floor we are on:\n");
	scanf("%d", &index);
	/*printf("Displaying information about floors :\n");
	for(i=0;i<n;i++)
		printf("State of floor %d is : %d\n",i , floor_state[i]);
	printf("Highest occupied floor : %d\n", high);
	printf("Lowest occupied floor : %d\n", low);*/
	i=traverse( index , stop);
	printf("The number of possible paths : %d\n", i);
	for(l=0;l < i;l++)
	{
		c=b[l];
		k=0;
		while(c[k+1] != -1 && c[k] != -1)
		{
			diff=fabs(c[k]-c[k+1]);
			sum+=diff;
			k++;	
		}
		if(sum < low1)
		{
			low1=sum;
			d=b[l];
		}
	}
	l=0;
	printf("The shortest distance :%d\n",low1);
	printf("The Shortest path is :\n");
	while(d[l] != -1)
	{
		printf("%d --> ", d[l]);
		l++;
	}
	return 0;
}

void up_to_none(int i)
{
	floor_state[i] = none; 
}

void down_to_none(int i)
{
	floor_state[i] = none;
}

void bothupdown_to_up(int i)
{
	floor_state[i] = up;
}

void bothupdown_to_down(int i)
{
	floor_state[i] = down;
}

void internal_to_none(int i)
{
	floor_state[i] = none;
}

void upandinternal_to_up(int i)
{
	floor_state[i] = up;
}

void upandinternal_to_none(int i)
{
	floor_state[i] = none;
}

void downandinternal_to_down(int i)
{
	floor_state[i] = down;
}

void downandinternal_to_none(int i)
{
	floor_state[i] = none;
}

void updownandinternal_to_up(int i)
{
	floor_state[i] = up;
}

void updownandinternal_to_down(int i)
{
	floor_state[i] = down;
}

int traverse(int index , enum lift lift_state)
{
	int i=0,p,q;
	if(index < 0 || index > (n-1))
	{
		j--;
		return 0;
	}
	if(high == low)
	{
		a[j++]=high;
		a[j]=-1;
		j--;
		b[k++]=a;
		return 1;
	}
	if(lift_state == stop && floor_state[index] == internal)
	{	
		internal_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	/*else if(lift_state == stop && floor_state[index] != internal)
		return traverse(index+1, up1) + traverse(index-1, down1);*/
	else if(lift_state == up1 && floor_state[index] == up)
	{
		up_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == up1 && floor_state[index] == bothupdown)
	{
		bothupdown_to_down(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == up1 && floor_state[index] == updownandinternal)
	{
		updownandinternal_to_down(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == up1 && floor_state[index] == upandinternal)
	{
		upandinternal_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == up1 && floor_state[index] == internal)
	{
		internal_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == up1 && floor_state[index] == downandinternal)
	{
		downandinternal_to_down(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == down)
	{
		down_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == bothupdown)
	{
		bothupdown_to_down(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == updownandinternal)
	{
		updownandinternal_to_up(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == downandinternal)
	{
		downandinternal_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == internal)
	{
		internal_to_none(index);
		a[j++] = index;
		if(index == high)
		{
			for(i=index-1;i>=0;i++)
			{
				if(floor_state[i] != none)
				{
					high=i;
					break;
				} 
			}
			//return traverse(high,down1);
			p=traverse(high,down1);
			j--;
			return p;
		}
		if(index == low)
		{
			for(i=index+1;i<n;i++)
			{
				if(floor_state[i] != none)
				{
					low=i;
					break;
				} 
			}
			//return traverse(low,up1);
			p=traverse(low,up1);
			j--;
			return p;
		}
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else if(lift_state == down1 && floor_state[index] == upandinternal)
	{
		upandinternal_to_up(index);
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
	else
	{
		a[j++] = index;
		//return traverse(index+1, up1) + traverse(index-1, down1);
		p=traverse(index+1, up1);
		j--;
		q=traverse(index-1, down1);
		j--;
		return p+q;
	}
}
