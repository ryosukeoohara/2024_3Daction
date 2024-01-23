xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 78;
 -2.91435;-19.38147;2.59595;,
 -0.16620;-19.38147;3.73739;,
 -0.16620;-12.00685;3.73739;,
 -2.91435;-12.00685;2.59595;,
 2.58196;-19.38147;2.59595;,
 2.58196;-12.00685;2.59595;,
 2.58196;-19.38147;2.59595;,
 3.72028;-19.38147;-0.15975;,
 3.72028;-12.00685;-0.15975;,
 2.58196;-12.00685;2.59595;,
 2.58196;-19.38147;-2.91545;,
 2.58196;-12.00685;-2.91545;,
 2.58196;-19.38147;-2.91545;,
 -0.16620;-19.38147;-4.05689;,
 -0.16620;-12.00685;-4.05689;,
 2.58196;-12.00685;-2.91545;,
 -2.91435;-19.38147;-2.91545;,
 -2.91435;-12.00685;-2.91545;,
 -2.91435;-19.38147;-2.91545;,
 -4.05267;-19.38147;-0.15975;,
 -4.05267;-12.00685;-0.15975;,
 -2.91435;-12.00685;-2.91545;,
 -2.91435;-19.38147;2.59595;,
 -2.91435;-12.00685;2.59595;,
 -0.16620;-9.98954;3.73739;,
 -2.91435;-9.98954;2.59595;,
 2.58196;-9.98954;2.59595;,
 3.72028;-9.98954;-0.15975;,
 2.58196;-9.98954;2.59595;,
 2.58196;-9.98954;-2.91545;,
 -0.16620;-9.98954;-4.05689;,
 2.58196;-9.98954;-2.91545;,
 -2.91435;-9.98954;-2.91545;,
 -4.05267;-9.98954;-0.15975;,
 -2.91435;-9.98954;-2.91545;,
 -2.91435;-9.98954;2.59595;,
 -0.16620;-5.93815;3.73739;,
 -2.91435;-5.93815;2.59595;,
 2.58196;-5.93815;2.59595;,
 3.72028;-5.93815;-0.15975;,
 2.58196;-5.93815;2.59595;,
 2.58196;-5.93815;-2.91545;,
 -0.16620;-5.93815;-4.05689;,
 2.58196;-5.93815;-2.91545;,
 -2.91435;-5.93815;-2.91545;,
 -4.05267;-5.93815;-0.15975;,
 -2.91435;-5.93815;-2.91545;,
 -2.91435;-5.93815;2.59595;,
 -0.16620;0.91473;3.71161;,
 -3.06161;0.91473;2.57772;,
 2.72922;0.91473;2.57772;,
 3.94490;0.91473;-0.15975;,
 2.72922;0.91473;2.57772;,
 2.72922;0.91473;-2.89722;,
 -0.16620;0.91473;-4.03111;,
 2.72922;0.91473;-2.89722;,
 -3.06161;0.91473;-2.89722;,
 -4.27729;0.91473;-0.15975;,
 -3.06161;0.91473;-2.89722;,
 -3.06161;0.91473;2.57772;,
 -0.16620;-19.38147;3.73739;,
 -2.91435;-19.38147;2.59595;,
 -0.16620;-19.38147;-0.15975;,
 2.58196;-19.38147;2.59595;,
 3.72028;-19.38147;-0.15975;,
 2.58196;-19.38147;-2.91545;,
 -0.16620;-19.38147;-4.05689;,
 -2.91435;-19.38147;-2.91545;,
 -4.05267;-19.38147;-0.15975;,
 -3.06161;0.91473;2.57772;,
 -0.16620;0.91473;3.71161;,
 -0.16620;3.78104;-0.47905;,
 2.72922;0.91473;2.57772;,
 3.94490;0.91473;-0.15975;,
 2.72922;0.91473;-2.89722;,
 -0.16620;0.91473;-4.03111;,
 -3.06161;0.91473;-2.89722;,
 -4.27729;0.91473;-0.15975;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;3,2,24,25;,
 4;2,5,26,24;,
 4;9,8,27,28;,
 4;8,11,29,27;,
 4;15,14,30,31;,
 4;14,17,32,30;,
 4;21,20,33,34;,
 4;20,23,35,33;,
 4;25,24,36,37;,
 4;24,26,38,36;,
 4;28,27,39,40;,
 4;27,29,41,39;,
 4;31,30,42,43;,
 4;30,32,44,42;,
 4;34,33,45,46;,
 4;33,35,47,45;,
 4;37,36,48,49;,
 4;36,38,50,48;,
 4;40,39,51,52;,
 4;39,41,53,51;,
 4;43,42,54,55;,
 4;42,44,56,54;,
 4;46,45,57,58;,
 4;45,47,59,57;,
 3;60,61,62;,
 3;63,60,62;,
 3;64,63,62;,
 3;65,64,62;,
 3;66,65,62;,
 3;67,66,62;,
 3;68,67,62;,
 3;61,68,62;,
 3;69,70,71;,
 3;70,72,71;,
 3;72,73,71;,
 3;73,74,71;,
 3;74,75,71;,
 3;75,76,71;,
 3;76,77,71;,
 3;77,69,71;;
 
 MeshMaterialList {
  1;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Photoshop\\neet12.jpg";
   }
  }
 }
 MeshNormals {
  37;
  -0.707792;0.000000;0.706421;,
  -0.000001;0.000000;1.000000;,
  0.707791;0.000000;0.706422;,
  1.000000;0.000000;-0.000000;,
  0.707791;0.000000;-0.706422;,
  -0.000001;0.000000;-1.000000;,
  -0.707792;0.000000;-0.706421;,
  -1.000000;0.000000;-0.000000;,
  -0.000001;0.000000;1.000000;,
  1.000000;0.000000;-0.000000;,
  0.707791;0.000000;-0.706422;,
  -0.000001;0.000000;-1.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.707792;0.000000;0.706421;,
  -0.000001;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  -0.707792;0.000000;-0.706421;,
  -1.000000;0.000000;0.000000;,
  -0.703625;-0.006855;0.710538;,
  -0.000001;-0.000509;1.000000;,
  0.703625;-0.006855;0.710539;,
  0.999912;-0.013234;-0.000000;,
  0.703625;-0.006855;-0.710539;,
  -0.000001;-0.000509;-1.000000;,
  -0.703625;-0.006855;-0.710538;,
  -0.999912;-0.013234;0.000000;,
  -0.613300;0.474004;0.631809;,
  -0.000001;0.478154;0.878276;,
  0.613299;0.474005;0.631810;,
  0.886185;0.463320;-0.003228;,
  0.619815;0.447486;-0.644659;,
  -0.000001;0.440742;-0.897634;,
  -0.619816;0.447486;-0.644658;,
  -0.886185;0.463319;-0.003228;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.999758;-0.021990;;
  48;
  4;0,1,8,0;,
  4;1,2,2,8;,
  4;2,3,9,2;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,6,11;,
  4;6,7,12,6;,
  4;7,0,0,12;,
  4;0,8,14,13;,
  4;8,2,2,14;,
  4;2,9,15,2;,
  4;9,10,4,15;,
  4;10,11,16,4;,
  4;11,6,17,16;,
  4;6,12,18,17;,
  4;12,0,13,18;,
  4;13,14,20,19;,
  4;14,2,21,20;,
  4;2,15,22,21;,
  4;15,4,23,22;,
  4;4,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,13,19,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,19,27,34;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;27,28,36;,
  3;28,29,36;,
  3;29,30,36;,
  3;30,31,36;,
  3;31,32,36;,
  3;32,33,36;,
  3;33,34,36;,
  3;34,27,36;;
 }
 MeshTextureCoords {
  78;
  0.295244;0.640011;,
  0.285704;0.640011;,
  0.285704;0.665609;,
  0.295244;0.665609;,
  0.276165;0.640011;,
  0.276165;0.665609;,
  0.296379;0.710463;,
  0.305944;0.710463;,
  0.305944;0.684864;,
  0.296379;0.684864;,
  0.315510;0.710463;,
  0.315510;0.684864;,
  0.316705;0.710463;,
  0.326244;0.710463;,
  0.326244;0.684864;,
  0.316705;0.684864;,
  0.335783;0.710463;,
  0.335783;0.684864;,
  0.336901;0.710463;,
  0.346466;0.710463;,
  0.346466;0.684864;,
  0.336901;0.684864;,
  0.356032;0.710463;,
  0.356032;0.684864;,
  0.285704;0.672612;,
  0.295244;0.672612;,
  0.276165;0.672612;,
  0.305944;0.677862;,
  0.296379;0.677862;,
  0.315510;0.677862;,
  0.326244;0.677862;,
  0.316705;0.677862;,
  0.335783;0.677862;,
  0.346466;0.677862;,
  0.336901;0.677862;,
  0.356032;0.677862;,
  0.285704;0.686675;,
  0.295244;0.686675;,
  0.276165;0.686675;,
  0.305944;0.663798;,
  0.296379;0.663798;,
  0.315510;0.663798;,
  0.326244;0.663798;,
  0.316705;0.663798;,
  0.335783;0.663798;,
  0.346466;0.663798;,
  0.336901;0.663798;,
  0.356032;0.663798;,
  0.285704;0.710463;,
  0.295755;0.710463;,
  0.275654;0.710463;,
  0.305944;0.640011;,
  0.296442;0.640011;,
  0.315447;0.640011;,
  0.326244;0.640011;,
  0.316193;0.640011;,
  0.336295;0.640011;,
  0.346466;0.640011;,
  0.336964;0.640011;,
  0.355969;0.640011;,
  0.325952;0.639645;,
  0.335492;0.635683;,
  0.325952;0.626117;,
  0.316413;0.635683;,
  0.312461;0.626117;,
  0.316413;0.616551;,
  0.325952;0.612589;,
  0.335492;0.616551;,
  0.339443;0.626117;,
  0.362946;0.635425;,
  0.366882;0.625374;,
  0.352335;0.625374;,
  0.362946;0.615324;,
  0.353443;0.611104;,
  0.343941;0.615324;,
  0.340005;0.625374;,
  0.343941;0.635425;,
  0.353443;0.639645;;
 }
}