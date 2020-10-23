#include "Box.h"
#include "BindableBase.h"
#include "Cube.h"
Box::Box(Graphics& gfx,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{
	namespace dx = DirectX;

	struct Vertex
	{
		dx::XMFLOAT3 pos;
		struct
		{
			float u;
			float v;
		} tex;
	};
	const auto model = Cube::MakeSkinned<Vertex>();

	AddBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

	auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader1.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(std::make_unique<PixelShader>(gfx, L"PixelShader1.cso"));

	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

	AddBind(std::make_unique<Texture>(gfx, L"Images\\cube.png"));

	
	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

void Box::Update(float dt) noexcept
{

	roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
