#version 130
// Once again, this preprocessor will only fail if your OpenGL version
// is horribly outdated.

// The fragment shader will get the values of these varying qualifiers
// from the vertex shader

uniform sampler2D tex;


// Another sample fragment shader is provided in the Spring 2015 midterm 2.
// You'd definitely want to take a look at that to know how to modify the
// colors based off of the positions, lighting, and normals. Plus you need
// to review for midterm 2 anyways, so why not start soon?
void main(){
   // Variables used for calculations declared here
   


   vec2 st = gl_TexCoord[0].st;
   
   vec2 stup = st;
   vec2 stdown = st;
   vec2 stleft = st;
   vec2 stright = st;

   stup[1] = st[1] + 1;
   stdown[1] = st[1] - 1;
   stleft[0] = st[0] - 1;
   stright[0] = st[0] + 1;

   vec4 mainColor = texture(tex, st);

   vec4 upColor = texture(tex, stup);
   vec4 downColor = texture(tex, stdown);
   vec4 leftColor = texture(tex, stleft);
   vec4 rightColor = texture(tex, stright);
   
   gl_FragColor = (mainColor + upColor + downColor + leftColor + rightColor) ;

   
}



