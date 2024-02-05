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
 75;
 -8.82105;-3.58371;-0.43420;,
 -0.78794;-12.06572;-6.04418;,
 0.00724;-2.78647;-0.18354;,
 -8.82224;-2.83082;-0.37359;,
 8.05186;-2.79906;-0.42341;,
 8.05304;-3.55194;-0.48403;,
 6.30075;-5.23938;-1.58606;,
 11.37888;-4.23996;-1.89356;,
 11.32714;-6.08445;-4.19219;,
 11.50987;-6.14137;-10.93798;,
 8.75470;-11.60468;-10.50366;,
 5.70000;-11.20337;-15.43605;,
 8.87258;-5.48163;-17.32948;,
 -0.04289;-10.66524;-18.86935;,
 -0.05540;-7.55460;-21.54184;,
 -5.76434;-11.22399;-15.40370;,
 -8.96698;-5.51372;-17.27915;,
 -11.60649;-6.18296;-10.87275;,
 -9.36247;-11.63624;-10.45383;,
 -10.76016;-4.27416;-1.83991;,
 -11.29871;-6.12469;-4.12907;,
 -8.82105;-3.58371;-0.43420;,
 -8.82224;-2.83082;-0.37359;,
 0.00272;0.02470;0.00456;,
 -8.82715;0.17121;-0.20064;,
 8.83070;0.20298;-0.25047;,
 11.33270;-0.69392;0.03718;,
 13.17736;-0.76183;-12.05997;,
 9.59196;-0.64056;-17.97822;,
 -0.06866;-1.70663;-23.04987;,
 -9.70429;-0.67527;-17.92377;,
 -13.06904;-0.80957;-12.24498;,
 -11.20640;-0.73118;0.09562;,
 -8.82715;0.17121;-0.20064;,
 -0.00587;3.33803;0.87327;,
 -8.83535;3.29368;0.68331;,
 8.82250;3.32544;0.63349;,
 10.97871;3.43817;-0.90298;,
 12.54261;3.78529;-11.09260;,
 8.84696;4.25739;-17.23319;,
 -0.07879;3.57680;-21.47183;,
 -8.98287;4.22532;-17.18288;,
 -12.61212;3.73998;-11.02153;,
 -11.01331;3.39861;-0.84093;,
 -8.83535;3.29368;0.68331;,
 -0.01783;8.10862;0.98455;,
 -4.00430;8.07006;0.79689;,
 3.96764;8.08440;0.77440;,
 10.86736;7.60672;-8.29311;,
 8.47016;8.04080;-11.92935;,
 -0.07536;9.07423;-15.47248;,
 -8.60260;8.01008;-11.92345;,
 -10.41872;7.67637;-9.75874;,
 -4.00430;8.07006;0.79689;,
 -0.78794;-12.06572;-6.04418;,
 -8.82105;-3.58371;-0.43420;,
 -0.02005;-13.95402;-12.88438;,
 8.05304;-3.55194;-0.48403;,
 6.30075;-5.23938;-1.58606;,
 11.37888;-4.23996;-1.89356;,
 5.70000;-11.20337;-15.43605;,
 8.75470;-11.60468;-10.50366;,
 -0.04289;-10.66524;-18.86935;,
 -5.76434;-11.22399;-15.40370;,
 -10.76016;-4.27416;-1.83991;,
 -9.36247;-11.63624;-10.45383;,
 -4.00430;8.07006;0.79689;,
 -0.01783;8.10862;0.98455;,
 -0.06751;11.44721;-12.68275;,
 3.96764;8.08440;0.77440;,
 10.86736;7.60672;-8.29311;,
 8.47016;8.04080;-11.92935;,
 -0.07536;9.07423;-15.47248;,
 -8.60260;8.01008;-11.92345;,
 -10.41872;7.67637;-9.75874;;
 
 58;
 4;0,1,2,3;,
 3;4,2,5;,
 3;5,2,6;,
 3;2,1,6;,
 4;5,7,8,4;,
 4;9,10,11,12;,
 4;11,13,14,12;,
 4;13,15,16,14;,
 4;17,18,19,20;,
 4;19,21,22,20;,
 4;3,2,23,24;,
 4;2,4,25,23;,
 4;4,8,26,25;,
 4;27,9,12,28;,
 4;12,14,29,28;,
 4;14,16,30,29;,
 4;31,17,20,32;,
 4;20,22,33,32;,
 4;24,23,34,35;,
 4;23,25,36,34;,
 4;25,26,37,36;,
 4;38,27,28,39;,
 4;28,29,40,39;,
 4;29,30,41,40;,
 4;42,31,32,43;,
 4;32,33,44,43;,
 4;35,34,45,46;,
 4;34,36,47,45;,
 4;36,37,48,47;,
 4;48,38,39,49;,
 4;39,40,50,49;,
 4;40,41,51,50;,
 3;52,42,43;,
 4;43,44,53,52;,
 3;54,55,56;,
 4;57,58,54,56;,
 3;59,57,56;,
 4;60,61,59,56;,
 3;62,60,56;,
 3;63,62,56;,
 4;64,65,63,56;,
 3;55,64,56;,
 3;66,67,68;,
 3;67,69,68;,
 3;69,70,68;,
 3;70,71,68;,
 3;71,72,68;,
 3;72,73,68;,
 3;73,74,68;,
 3;74,66,68;,
 4;41,42,52,51;,
 4;30,31,42,41;,
 4;16,17,31,30;,
 4;15,18,17,16;,
 3;37,38,48;,
 4;26,27,38,37;,
 4;8,9,27,26;,
 4;7,10,9,8;;
 
 MeshMaterialList {
  6;
  58;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Documentsneet.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\neett.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\neett.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV_Grid.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV_Grid.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  66;
  -0.068585;-0.591190;0.803611;,
  0.205536;-0.603528;0.770396;,
  0.189445;-0.613156;0.766910;,
  0.654070;0.753833;0.062673;,
  0.489592;-0.657256;-0.572987;,
  -0.000477;-0.758744;-0.651389;,
  -0.446902;-0.793166;-0.413723;,
  -0.321233;-0.851778;0.413863;,
  -0.045978;-0.242072;0.969168;,
  0.000063;-0.271840;0.962343;,
  0.047377;-0.160899;0.985833;,
  0.655746;-0.389462;-0.646774;,
  -0.001799;-0.422470;-0.906375;,
  -0.656081;-0.379566;-0.652294;,
  -0.846499;-0.458414;0.270733;,
  -0.113617;-0.169850;0.978898;,
  0.003476;-0.164387;0.986390;,
  0.110130;-0.168330;0.979559;,
  0.190830;-0.170361;0.966727;,
  0.691292;-0.008636;-0.722524;,
  -0.002883;0.013523;-0.999904;,
  -0.696267;-0.009761;-0.717716;,
  -0.990520;-0.053407;0.126561;,
  -0.116104;-0.094517;0.988730;,
  0.003094;-0.138956;0.990294;,
  0.122547;-0.093686;0.988031;,
  0.790524;0.340731;0.508896;,
  0.605026;0.481311;-0.634258;,
  -0.003167;0.552039;-0.833812;,
  -0.606652;0.468406;-0.642315;,
  -0.843624;0.471791;0.256342;,
  -0.034146;-0.012722;0.999336;,
  0.002844;-0.012636;0.999916;,
  0.039830;-0.012532;0.999128;,
  0.617522;0.784517;0.056567;,
  0.444119;0.774690;-0.450126;,
  -0.002180;0.772152;-0.635434;,
  -0.445103;0.761392;-0.471344;,
  -0.598833;0.800631;0.019719;,
  -0.116592;-0.984783;0.128874;,
  -0.005497;0.994299;-0.106488;,
  -0.922743;0.347596;-0.166502;,
  -0.981975;-0.043919;-0.183836;,
  -0.890969;-0.439141;-0.115453;,
  -0.593502;-0.803068;0.053265;,
  0.931876;0.328136;-0.154703;,
  0.980875;-0.040948;-0.190281;,
  0.879862;-0.460453;-0.117584;,
  0.586451;-0.807999;0.056676;,
  0.193692;-0.669479;0.717134;,
  -0.680820;0.702088;0.208700;,
  0.377355;-0.574834;0.726064;,
  -0.115674;-0.339918;0.933314;,
  -0.204510;-0.174914;0.963110;,
  -0.285981;-0.003612;0.958228;,
  0.470260;0.748903;0.466905;,
  0.261371;0.918735;0.295993;,
  -0.462315;0.790428;0.401857;,
  -0.268291;0.924932;0.269297;,
  -0.678300;-0.724281;0.123797;,
  0.570145;-0.773268;0.277473;,
  0.310423;-0.855220;0.415014;,
  0.198044;-0.956548;0.213998;,
  -0.001078;0.971435;0.237302;,
  0.991322;-0.048004;0.122382;,
  0.974436;-0.205915;0.089849;;
  58;
  4;0,1,9,8;,
  3;10,9,2;,
  3;2,9,49;,
  3;9,1,49;,
  4;3,3,3,3;,
  4;47,48,4,11;,
  4;4,5,12,11;,
  4;5,6,13,12;,
  4;43,44,7,14;,
  4;50,50,50,50;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,51,18,17;,
  4;46,47,11,19;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;42,43,14,22;,
  4;52,8,15,53;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;45,46,19,27;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;41,42,22,30;,
  4;53,15,23,54;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;55,26,34,56;,
  4;34,45,27,35;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  3;38,41,30;,
  4;30,57,58,38;,
  3;59,59,39;,
  4;2,49,1,60;,
  3;61,2,39;,
  4;62,48,61,39;,
  3;5,4,39;,
  3;6,5,39;,
  4;7,44,6,39;,
  3;0,7,39;,
  3;58,63,40;,
  3;63,56,40;,
  3;56,34,40;,
  3;34,35,40;,
  3;35,36,40;,
  3;36,37,40;,
  3;37,38,40;,
  3;38,58,40;,
  4;29,41,38,37;,
  4;21,42,41,29;,
  4;13,43,42,21;,
  4;6,44,43,13;,
  3;26,45,34;,
  4;64,46,45,26;,
  4;65,47,46,64;,
  4;61,48,47,51;;
 }
 MeshTextureCoords {
  75;
  0.739493;0.926134;,
  0.746447;0.926134;,
  0.746447;0.905218;,
  0.739493;0.905218;,
  0.753402;0.905218;,
  0.753402;0.926134;,
  0.752023;0.926134;,
  0.760356;0.926134;,
  0.760356;0.905218;,
  0.764885;0.905218;,
  0.764884;0.926134;,
  0.767311;0.926134;,
  0.767311;0.905218;,
  0.774266;0.926134;,
  0.774266;0.905218;,
  0.781220;0.926134;,
  0.781220;0.905218;,
  0.783647;0.905218;,
  0.783647;0.926134;,
  0.788175;0.926134;,
  0.788175;0.905218;,
  0.795129;0.926134;,
  0.795129;0.905218;,
  0.746447;0.884302;,
  0.739493;0.884302;,
  0.753402;0.884302;,
  0.760356;0.884302;,
  0.764900;0.884302;,
  0.767311;0.884302;,
  0.774266;0.884302;,
  0.781220;0.884302;,
  0.783631;0.884302;,
  0.788175;0.884302;,
  0.795129;0.884302;,
  0.746447;0.863386;,
  0.739493;0.863386;,
  0.753402;0.863386;,
  0.760356;0.863386;,
  0.764397;0.863386;,
  0.767311;0.863386;,
  0.774266;0.863386;,
  0.781220;0.863386;,
  0.784134;0.863386;,
  0.788175;0.863386;,
  0.795129;0.863386;,
  0.746447;0.842470;,
  0.739493;0.842470;,
  0.753402;0.842470;,
  0.760356;0.842470;,
  0.767311;0.842470;,
  0.774266;0.842470;,
  0.781220;0.842470;,
  0.788175;0.842470;,
  0.795129;0.842470;,
  0.767311;0.995679;,
  0.791899;0.985495;,
  0.767311;0.962297;,
  0.742723;0.985495;,
  0.747596;0.987513;,
  0.732538;0.960907;,
  0.742723;0.936318;,
  0.739168;0.944900;,
  0.767311;0.926134;,
  0.791899;0.936318;,
  0.802084;0.960907;,
  0.795454;0.944900;,
  0.791899;0.783318;,
  0.767311;0.773133;,
  0.767311;0.809297;,
  0.742723;0.783318;,
  0.732538;0.807906;,
  0.742723;0.832494;,
  0.767311;0.842679;,
  0.791899;0.832494;,
  0.802084;0.807906;;
 }
}
