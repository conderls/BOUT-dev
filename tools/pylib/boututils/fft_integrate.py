import numpy as np
from pylab import plot, show

def fft_integrate(y, loop=None):
    try:  # If an error occurs, return to caller

        n = np.size(y)
    
        f = np.fft.fft(y)/n
        imag = np.complex(0.0, 1.0)

        result = np.arange(n)*f[0]
        loop = np.float(n)*f[0] # return the loop integral

        f[0] = 0.0

        if (n % 2) == 0 :
            # even number of points

            for i in range (1, n/2) :
                a = imag*2.0*np.pi*np.float(i)/np.float(n)
                f[i] = f[i] / a         # positive frequencies
                f[n-i] = - f[n-i] / a   # negative frequencies
             

            f[n/2] = f[n/2] / (imag*np.pi)
        else:
            # odd number of points

            for i in range (1, (n-1)/2+1):
                a = imag*2.0*np.pi*np.float(i)/np.float(n)
                f[i] = f[i] / a
                f[n-i] = - f[n-i] / a
             

        result = result + np.fft.ifft(f)*n
    
        result = result - result[0] # just to make sure
    
        return result
    except:
        print 'fft_integrate_fail'



def test_integrate():

    n = 10
    dx = 2.0*np.pi/np.float(n)
    x = dx * np.arange(n)

    y = 1 + np.cos(x) - 0.5*np.sin(2*x)
    iy = x + np.sin(x) + 0.25*np.cos(2*x)
    

    result = fft_integrate(y)*dx

    plot( x, iy)
    plot( x, result, 'x')
    show() 