#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "gnuplot_i.hpp"

void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    stg::cout << std::endl << "Press any key to continue..." << std::endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}

//========================
// Draw a Barnsley fern
//========================
// http://en.wikipedia.org/wiki/Barnsley_fern
// http://www.home.aone.net.au/~byzantium/ferns/fractal.html

int main()
{
	try
	{
		// define the max number of points, needed for gerneration of the image
		const unsigned int uiMaxPoints(1E+6);
		// local buffers
        std::vector<double> x(uiMaxPoints), y(uiMaxPoints);

		// init with starting values: x = 0, and y = 0;
		// Note: the iteration starts with index = 1

		/*
			 The starting shapes for Barnsley's Fern can be specified as a series of 28 numbers to feed into the calculation process. These are as follows:

			 	0	   0	  0    .16     0	  0    .01
			   .85   .04   -.04    .85     0	1.6    .85
			   .2	-.26	.23    .22     0	1.6    .07
			  -.15   .28	.26    .24     0	 .44   .07
			 The four lines correspond in general terms to the rachis of the fern (first row), the overall form of the frond (second row), the left hand first 
			 pinna (third row) and the right hand first pinna (final row). The first four columns correspond (roughly) to things like the length of the pinna, 
             the sparseness and width of the pinnae, the curve of the frond and pinnae etc. The exact relationships are very complex. The fifth column is a list 
			 of probabilities that tell the calculation process how often to use the particular rows. It gives the balance to the final picture. Transforming these 
			 iteratively is simple but exceedingly labor intensive. Just the job for a computer.
		*/
/*		x[0] = 0.0; y [0] = 0.0;
		// init random generator 
 		srand ( time(NULL) + getuid() );
		for(int i = 1; i < uiMaxPoints;++i)
		{
			double dRandVal( (rand() % 100 + 1) /102. );
			if (dRandVal < 0.01)
			{
			    x[i] = 0;
			    y[i] = 0.16 * y[i-1];
			}
			else if (dRandVal < 0.08)
			{
			    x[i] = 0.2 *x[i-1] - 0.26*y[i-1];
			    y[i] = 0.23*x[i-1] + 0.22*y[i-1] + 1.6;
			}
			else if (dRandVal < 0.15)
			{
			    x[i] = -0.15*x[i-1] + 0.28*y[i-1];
			    y[i] =  0.26*x[i-1] + 0.24*y[i-1] + 0.44;
			}
			else
			{
			    x[i] =  0.85*x[i-1] + 0.04*y[i-1];
			    y[i] = -0.04*x[i-1] + 0.85*y[i-1] + 1.6;
			}
		}
*/

		/*
			  another version:
			   0	 0     0	  .2	 0   -0.12    .01
			  .845  .035  -.035    .82    0    1.6     .85
			  .2   -.31    .255    .245   0 	.29    .07
			 -.15	.24    .25     .20    0 	.68    .07

		*/

		x[0] = 0.0; y [0] = 0.0;
		// init random generator 
 		srand ( time(NULL) + getuid() );
		for(int i = 1; i < uiMaxPoints;++i)
		{
			double dRandVal( (rand() % 100 + 1) /102. );
			if (dRandVal < 0.01)
			{
			    x[i] = 0;
			    y[i] = .2 * y[i-1];
			}
			else if (dRandVal < 0.08)
			{
			    x[i] = 0.2  *x[i-1] - 0.31*y[i-1];
			    y[i] = .255 *x[i-1] + .245*y[i-1] + .29;
			}
			else if (dRandVal < 0.15)
			{
			    x[i] = -0.15*x[i-1] + 0.24*y[i-1];
			    y[i] =  0.25*x[i-1] + 0.2 *y[i-1] + 0.68;
			}
			else
			{
			    x[i] =  .845*x[i-1] + .035*y[i-1];
			    y[i] = -.035*x[i-1] + .82 *y[i-1] + 1.6;
			}
		}
			
		// configure the gnuplot interface
		Gnuplot gplt;
		gplt.cmd("set noborder");
		gplt.cmd("set noxtics");
		gplt.cmd("set noytics");
		gplt.cmd("set pointsize 0.2");
		gplt.cmd("set key left");
		gplt.cmd("set size square");
		gplt.set_style("points");
		// send values to gnuplot 
		gplt.plot_xy(x, y, "Barnsley fern");

 		wait_for_key ();
    }
    catch(GnuplotException & ge)
    {
        std::cerr << ge.what() << std::endl;
    }
	return 0;
}

