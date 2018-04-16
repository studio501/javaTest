package myjni;

public class HelloWorld {
	static {
		System.loadLibrary("hello");
	}

	private native void sayHello();
	private native double average(int n1,int n2);

	private native void others();
	private native String passStrfromJava(String msg);
	private native double[] sumAndAverage(double[] numbers);
	private native void modifyInstanceMember();

	private int _number = 88;
	private String _msg = "a str in java";
	private int[] _intArr = {1,2,3,4,5};

	private static double _s_number = 22.33;

	private native void nativeMethod();

	//to be called back by the native code
	private void callback(){
		System.out.print("callback in java\n");
	}

	private void callback(String msg){
		System.out.print("callback in java " + msg + "\n");
	}

	private double callbackAverage(int n1,int n2)
	{
		return ((double) n1 + n2 ) / 2.0;
	}

	//static method to be called back
	private static String callbackStatic(){
		return "callbackStatic in java ...\n";
	}

    public static void main(String[] args) {
		HelloWorld hw = new HelloWorld();
		hw.sayHello();
		hw.others();
		String result = hw.passStrfromJava("str from java!");
		System.out.print(result);
		System.out.print(hw.average(100,200)+"\n");

		double[] numbers = {11.2,22,33.9};
		double[] result2 = hw.sumAndAverage(numbers);
		for(int i=0;i<result2.length;i++){
			System.out.print(result2[i]+ ((i == result2.length - 1) ? "" : "," ));	
		}

		System.out.print("\nbefore modify: "+hw._number+" "+hw._msg+" "+_s_number);
		hw.modifyInstanceMember();
		System.out.print("after modify: "+hw._number+" "+hw._msg +" " + _s_number + "\n");
		for(int i=0;i<hw._intArr.length;i++){
			System.out.print(hw._intArr[i]+ ((i == hw._intArr.length - 1) ? "" : "," ));	
		}

		hw.nativeMethod();
		System.out.print("\n");
    }
}