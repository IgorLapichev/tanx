#pragma once

template <typename T> class Platform
{
public:
	Platform(std::shared_ptr <T> entity) { m_entity = entity; }

	virtual void step(const double &time) final
	{
		std::get<0>(m_entity->m_position) += m_speed * int(cos(m_direction));
		std::get<1>(m_entity->m_position) += m_speed * int(sin(m_direction));
	}

	const std::shared_ptr <T> getEntity() const 
	{ 
		return m_entity;
	}

private:
	std::shared_ptr <T> m_entity = std::make_shared <T> ();
	double m_direction = 0;
	int m_speed = 0;
};

