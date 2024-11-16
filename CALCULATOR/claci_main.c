#include"header.h"
main()
{
	char s[50];
	int ele;
	int res,a[20];
	uart0_init(9600);
	lcd_init();

	while(1)
	{ 	
	lcd_cmd(0xc0);
	uart0_tx_string("Enter ex:\r\n");
	lcd_string("Enter ex:");
	uart0_rx_string(s,50);
	int_fun(s,a,&ele);
	res=calculation(a,ele);
	uart0_tx_string("\r\n");
	uart0_tx_string("\r\nresult=");
	uart0_atoi(res);
	uart0_tx_string("\r\n\r\n");
	lcd_cmd(0x80);
	lcd_string("Result=");
	lcd_atoi(res);
	}
}
int bracket(int *a,int *ele)
{
	int i,n=*ele,d[30]={0},j,k,p,x,o;
	for(i=0;i<n;i++)
	{
		uart0_tx_string("\r\ni= ");
						uart0_atoi(i);
						uart0_tx_string("\r\n");
		if(a[i]=='(')
		{	
						uart0_tx_string("\r\na[i]= ");
						uart0_atoi(i);
						uart0_tx_string("\r\n");
			for(j=i+1,x=0;j<n;j++)
			{
				if(a[j]==')')
				{
						uart0_tx_string("\r\n");
						for(o=0;o<x;o++)
						{
						uart0_atoi(d[o]);
						uart0_tx(' ');
						}
						a[i]=calculation(d,x);
						uart0_tx_string("d[i]= ");
						uart0_atoi(i);
						uart0_tx_string("\r\n");
						for(k=i+1,p=j+1;p<n;p++,k++)
							a[k]=a[p];
						n-=x;
						break;
				}
				d[x++]=a[j];
			}
		}
	}
	*ele=n;
	uart0_tx_string("\r\n");
	for(i=0;i<*ele;i++)
	{
	uart0_atoi(a[i]);
	uart0_tx(' ');
	}
	return calculation(a,*ele);
	
}






void int_fun(char *s,int *a,int *ele)
{
	int i,j=0,sum=0;
	for(i=0;s[i];i++)
	{
		if(s[i]>='0' && s[i]<='9')
			sum=sum*10+(s[i]-48);
		else
		{	
			//else
			//{	///if(a[j-1]!=')')
				a[j++]=sum;
				if(s[i]=='('||s[i]==')')
				a[j]=s[i];
				else
				a[j++]=s[i];
			//}
			sum=0;
		}
	}
	a[j++]=sum;
	*ele=j;
}
int calculation(int *a,int ele)
{
	int i,j;
	int res=0,n1,n2; 
	for(i=1;i<ele;i+=2)
	{
		if(a[i]=='*'||a[i]=='/')
		{
			n1=a[i-1];
			n2=a[i+1];
			if(a[i]=='*')
				res=n1*n2;
			else if(a[i]=='/')
				res=n1/n2;
			a[i-1]=res;
			for(j=i;j<ele-2;j++)
				a[j]=a[j+2];
			ele-=2;
			i-=2;
		}	
	}
	for(i=1;i<ele;i+=2)
	{
		if(a[i]=='+'||a[i]=='-')
		{
			n1=a[i-1];
			n2=a[i+1];
			if(a[i]=='+')
				res=n1+n2;
			else if(a[i]=='-')
				res=n1-n2;
			a[i-1]=res;
			for(j=i;j<ele-2;j++)
				a[j]=a[j+2];
			ele-=2;
				i-=2;
		}	
	}
	return res;
}







