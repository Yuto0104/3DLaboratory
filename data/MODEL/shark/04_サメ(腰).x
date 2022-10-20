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
 72;
 8.98114;15.74710;-5.43536;,
 8.54300;15.54676;-0.00652;,
 9.72924;7.38788;-0.00652;,
 10.22804;7.17096;-5.43536;,
 7.61447;15.12221;5.77291;,
 8.67214;7.84757;5.77291;,
 8.50038;4.15540;-0.00652;,
 8.93634;3.77318;-5.43536;,
 7.57647;4.96543;5.77291;,
 7.61447;15.12221;5.77291;,
 4.21676;18.85593;5.77291;,
 4.21676;10.37352;5.77291;,
 8.67214;7.84757;5.77291;,
 -0.02445;21.36776;5.77291;,
 -0.02445;10.37352;5.77291;,
 -4.26565;18.85593;5.77291;,
 -4.26565;10.37352;5.77291;,
 -7.66336;15.12221;5.77291;,
 -8.72104;7.84757;5.77291;,
 4.21676;2.38550;5.77291;,
 7.57647;4.96543;5.77291;,
 -0.02445;1.89109;5.77291;,
 -4.26565;2.38550;5.77291;,
 -7.62536;4.96543;5.77291;,
 -7.66336;15.12221;5.77291;,
 -8.59189;15.54676;-0.00652;,
 -9.77813;7.38788;-0.00652;,
 -8.72104;7.84757;5.77291;,
 -9.03003;15.74710;-5.43536;,
 -10.27693;7.17096;-5.43536;,
 -8.54927;4.15540;-0.00652;,
 -7.62536;4.96543;5.77291;,
 -8.98523;3.77318;-5.43536;,
 -4.26565;18.85593;5.77291;,
 -4.78118;19.73434;-0.00652;,
 -8.59189;15.54676;-0.00652;,
 -0.02445;22.55148;-0.00652;,
 4.21676;18.85593;5.77291;,
 4.73229;19.73434;-0.00652;,
 8.54300;15.54676;-0.00652;,
 -5.02445;20.14883;-5.43536;,
 -9.03003;15.74710;-5.43536;,
 -0.02445;23.11004;-5.43536;,
 4.97555;20.14883;-5.43536;,
 8.98114;15.74710;-5.43536;,
 -8.54927;4.15540;-0.00652;,
 -4.78118;1.26187;-0.00652;,
 -4.26565;2.38550;5.77291;,
 -0.02445;0.70738;-0.00652;,
 4.73229;1.26187;-0.00652;,
 4.21676;2.38550;5.77291;,
 8.50038;4.15540;-0.00652;,
 -8.98523;3.77318;-5.43536;,
 -5.02445;0.73167;-5.43536;,
 -0.02445;0.14882;-5.43536;,
 4.97555;0.73167;-5.43536;,
 8.93634;3.77318;-5.43536;,
 -9.03003;15.74710;-5.42218;,
 -5.02445;20.14883;-5.42216;,
 -5.02445;10.14882;-5.42216;,
 -10.27695;7.17096;-5.42218;,
 -0.02445;23.11004;-5.42214;,
 -0.02445;10.14882;-5.42214;,
 4.97555;20.14883;-5.42211;,
 4.97555;10.14882;-5.42211;,
 8.98115;15.74710;-5.42209;,
 10.22805;7.17096;-5.42208;,
 -5.02445;0.73167;-5.42216;,
 -8.98523;3.77318;-5.42219;,
 -0.02445;0.14882;-5.42214;,
 4.97555;0.73167;-5.42211;,
 8.93634;3.77318;-5.42208;;
 
 40;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;13,15,16,14;,
 4;15,17,18,16;,
 4;12,11,19,20;,
 4;11,14,21,19;,
 4;14,16,22,21;,
 4;16,18,23,22;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;27,26,30,31;,
 4;26,29,32,30;,
 4;24,33,34,35;,
 4;33,13,36,34;,
 4;13,37,38,36;,
 4;37,4,39,38;,
 4;35,34,40,41;,
 4;34,36,42,40;,
 4;36,38,43,42;,
 4;38,39,44,43;,
 4;45,46,47,31;,
 4;46,48,21,47;,
 4;48,49,50,21;,
 4;49,51,8,50;,
 4;52,53,46,45;,
 4;53,54,48,46;,
 4;54,55,49,48;,
 4;55,56,51,49;,
 4;57,58,59,60;,
 4;58,61,62,59;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;60,59,67,68;,
 4;59,62,69,67;,
 4;62,64,70,69;,
 4;64,66,71,70;;
 
 MeshMaterialList {
  5;
  40;
  1,
  1,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  4,
  4,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.194510;0.304314;0.461176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\3D表\現技術(後期)\\作品\\Ver.1.1(試作3号)\\data\\TEXTURE\\口.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  54;
  0.900634;0.425494;0.088389;,
  0.896339;0.423478;0.131313;,
  0.989515;-0.108563;0.095256;,
  0.984083;-0.107715;0.141345;,
  0.797860;-0.593476;0.105857;,
  0.792496;-0.589370;0.156821;,
  0.890378;0.420675;0.173952;,
  0.000000;0.000000;1.000000;,
  0.976537;-0.106636;0.187096;,
  0.785048;-0.583714;0.207311;,
  -0.896339;0.423478;0.131313;,
  -0.900635;0.425494;0.088389;,
  -0.984083;-0.107715;0.141345;,
  -0.989515;-0.108562;0.095256;,
  -0.792496;-0.589370;0.156820;,
  -0.797860;-0.593476;0.105857;,
  -0.626310;0.768743;0.129498;,
  -0.505189;0.853010;0.130989;,
  0.626310;0.768743;0.129498;,
  -0.629196;0.772344;0.087162;,
  -0.507594;0.857072;0.088182;,
  0.629196;0.772344;0.087162;,
  -0.371172;-0.915007;0.158093;,
  -0.000000;-0.988428;0.151691;,
  0.371172;-0.915007;0.158093;,
  -0.373799;-0.921348;0.106732;,
  -0.000000;-0.994749;0.102347;,
  0.373799;-0.921348;0.106732;,
  0.000004;-0.000000;-1.000000;,
  0.000005;-0.000000;-1.000000;,
  0.000006;0.000000;-1.000000;,
  0.000005;0.000000;-1.000000;,
  0.000005;0.000001;-1.000000;,
  0.000005;0.000000;-1.000000;,
  0.000006;0.000000;-1.000000;,
  0.000005;-0.000000;-1.000000;,
  0.000006;0.000002;-1.000000;,
  0.000006;0.000001;-1.000000;,
  0.000005;-0.000000;-1.000000;,
  0.000005;0.000000;-1.000000;,
  0.000005;-0.000000;-1.000000;,
  0.000005;-0.000000;-1.000000;,
  -0.890378;0.420675;0.173952;,
  -0.976537;-0.106636;0.187096;,
  -0.785048;-0.583714;0.207311;,
  -0.622289;0.763750;0.171589;,
  -0.501847;0.847366;0.173554;,
  0.501847;0.847366;0.173554;,
  0.622289;0.763750;0.171589;,
  0.505189;0.853010;0.130989;,
  0.507594;0.857072;0.088182;,
  -0.367553;-0.906220;0.208971;,
  0.000000;-0.979663;0.200650;,
  0.367553;-0.906221;0.208971;;
  40;
  4;0,1,3,2;,
  4;1,6,8,3;,
  4;2,3,5,4;,
  4;3,8,9,5;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;42,10,12,43;,
  4;10,11,13,12;,
  4;43,12,14,44;,
  4;12,13,15,14;,
  4;42,45,16,10;,
  4;45,46,17,16;,
  4;47,48,18,49;,
  4;48,6,1,18;,
  4;10,16,19,11;,
  4;16,17,20,19;,
  4;49,18,21,50;,
  4;18,1,0,21;,
  4;14,22,51,44;,
  4;22,23,52,51;,
  4;23,24,53,52;,
  4;24,5,9,53;,
  4;15,25,22,14;,
  4;25,26,23,22;,
  4;26,27,24,23;,
  4;27,4,5,24;,
  4;28,29,33,32;,
  4;29,30,34,33;,
  4;30,31,35,34;,
  4;31,39,40,35;,
  4;32,33,37,36;,
  4;33,34,30,37;,
  4;34,35,38,30;,
  4;35,40,41,38;;
 }
 MeshTextureCoords {
  72;
  0.333333;0.000000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  0.333333;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.666667;1.000000;,
  0.333333;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  0.250000;0.000000;,
  0.250000;0.333333;,
  0.000000;0.333333;,
  0.500000;0.333333;,
  0.750000;0.000000;,
  0.750000;0.333333;,
  1.000000;0.333333;,
  0.250000;0.666667;,
  0.000000;0.666667;,
  0.500000;0.666667;,
  0.750000;0.666667;,
  1.000000;0.666667;,
  0.000000;0.666667;,
  0.250000;0.666667;,
  0.250000;1.000000;,
  0.500000;0.666667;,
  0.750000;0.666667;,
  0.750000;1.000000;,
  1.000000;0.666667;,
  0.000000;0.333333;,
  0.250000;0.333333;,
  0.500000;0.333333;,
  0.750000;0.333333;,
  1.000000;0.333333;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;;
 }
}
