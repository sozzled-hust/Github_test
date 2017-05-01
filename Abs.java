import java.util.Scanner;

public class Abs {
//main 函数
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		
		System.out.print("Print the number to get it's abstruct:");
		int n = in.nextInt();
		System.out.println("abs(int)="+abs(n));
		
		System.out.print("Print anther number(double) to get it's abstruct: ");
		double x = in.nextDouble();
		System.out.println("abs(double)="+abs1(x));
		
		System.out.print("Enter the number(Prime or not) you want to get:");
		int n1 = in.nextInt();
		System.out.println("isPrime="+isPrime(n1));
		
		System.out.print("Enter the number to get it's sqrt:");
		double n2 = in.nextDouble();
		System.out.println("sqrt(n2)="+sqrt(n2));
		
		System.out.print("Now we will get the hypotenuse");
		System.out.print("Enter the a=");
		double a = in.nextDouble();
		System.out.print("Enter the b=");
		double b = in.nextDouble();
		System.out.println("hypotenuse="+hypotenuse(a,b));
		
		System.out.print("Now enter the number N:");
		int N = in.nextInt();
		System.out.println("sum="+H(N));
		
		
//计算一个整型的绝对值
	}
	public static int abs(int n){
	if(n<0)
		return -n;
	else
		return n;
	}
//计算一个浮点型的绝对值	
	public static double abs1(double x){
		if(x<0.0)
			return -x;
		else
			return x;	
	}
//判定一个数是否是素数
	public static boolean isPrime(int N){
		if(N<2)
			return false;
		for(int i=2;i*i<=N;i++)
			if(N%i==0)
				return false;
		return true;
	}
//计算平方根
	public static double sqrt(double c){
		if(c<0)
			return Double.NaN;
		double err = 1e-15;
		double t=c;
		while(Math.abs(t - c/t)>err*t)
			t=(c/t+t)/2.0;
		return t;
	}
	//计算直角三角形的斜边
	public static double hypotenuse(double a, double b){
		return Math.sqrt(a*a+b*b);
	}
	//计算调和级数
	public static double H(int N)
	{
		double sum = 0.0;
		for(int i=1;i<=N;i++)
			sum+=1.0/i;
		return sum;
	}
}