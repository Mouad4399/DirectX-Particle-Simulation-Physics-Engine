# DirectX-Particle-Simulation-Physics-Engine
A small C++ project! 🎮
using Chili Framework

# Demo 


https://github.com/user-attachments/assets/04f06a64-5c83-4926-8ddf-0e6044b9462c



As a recent Computer Science graduate, I’ve been diving deep into creating dynamic simulations and exploring the power of DirectX. I built a particle collision simulation from scratch, adding interactive features that make the project both educational and fun to use. Here are some highlights:

🔹 Particle Control: Use arrow keys to move a green particle and control all particles by clicking and launching them with the mouse. 

🔹 Dynamic Particle Management: Easily add or delete particles in real-time. 

🔹 Spring Effect: Press "S" to activate a spring effect, transforming particles into a polygonal shape. This dynamic spring constraint makes the particles behave like a connected jelly or slime, bouncing off walls and maintaining the polygon shape. 


By specifying the spring length, you can make the particles form any desired shape. I designed a specific formula that generates the spring length automatically for regular n-sided polygons, along with an equation to help determine if the mouse is inside the polygon. This method can be more efficient than ray-casting in this specific case.

In this project, I utilized basic Linear Algebra concepts and physics equations to bring these features to life, all out of curiosity and passion for learning.
Check out the demo video showcasing the project in action.

# the n-side polygon general equation I invented for this project :

where:

$$(i,j)$$ is the vector for translation 

$$r$$ is the rotation

$$n$$ is the number of sides you want 
```math


(sqrt{((cos((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+cos(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r)))^{2}+((\sin((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+\sin(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r)))^{2}})^{-1}*((x-i)*((cos((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+cos(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r)))+(y-j)*((\sin((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+\sin(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r))))=\frac{(sqrt{((cos((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+cos(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r)))^{2}+((\sin((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})*2*\frac{pi}{n})+r)+\sin(((floor(\frac{atan2((y-j),(x-i))-r}{2*\frac{pi}{n}})+1)*2*\frac{pi}{n})+r)))^{2}})}{2}

```


like if we say I want a $$x,y$$ vector that exist between k*pi/n and k*pi/n +1 ,its the projection (scalar produt) on the center vector that also exist in the same k *pi/n and k*pi/n +1 should be equal to half of norm of that center vector , this scalar product is just to maintain the same scale of the polygons in order to be overlapped with the 1 raduis circle otherwise when changing the n the polygons will be different in size.
