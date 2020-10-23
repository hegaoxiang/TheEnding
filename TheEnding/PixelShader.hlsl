cbuffer CBuf
{
    float4 face_colors[6];
};

float4 main() : SV_Target
{
    return face_colors[2];
}