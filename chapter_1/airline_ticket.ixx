export module airline_ticket;
import <string>;
import <optional>;

export class AirlineTicket
{
private:
	std::string m_passengerName{ "Unknown Passenger" };
	int m_numberOfMiles{ 0 };
	int m_frequentFlyerNumber{ 0 };
	bool m_hasEliteSuperRewardsStatus{ false };
public:
	double calculatePriceInDollars();

	std::string getPassengerName() const;
	void setPassengerName(const std::string& name);

	int getNumberOfMiles() const;
	void setNumberOfMiles(const int miles);

	bool hasEliteSuperRewardsStatus() const;
	void setEliteSuperRewardsStatus(const bool status);

	std::optional<int> getFrequentFlyerNumber();
	void setFrequentFlyerNumber(const bool freqNumber);
};

double AirlineTicket::calculatePriceInDollars()
{
	if (hasEliteSuperRewardsStatus())
	{
		return 0.0;
	}
	return getNumberOfMiles() * 0.1;
}

std::string AirlineTicket::getPassengerName() const
{
	return m_passengerName;
}

void AirlineTicket::setPassengerName(const std::string& name)
{
	m_passengerName = name;
}

int AirlineTicket::getNumberOfMiles() const
{
	return m_numberOfMiles;
}

void AirlineTicket::setNumberOfMiles(const int miles)
{
	m_numberOfMiles = miles;
}

bool AirlineTicket::hasEliteSuperRewardsStatus() const
{
	return m_hasEliteSuperRewardsStatus;
}

void AirlineTicket::setEliteSuperRewardsStatus(const bool status)
{
	m_hasEliteSuperRewardsStatus = status;
}

std::optional<int> AirlineTicket::getFrequentFlyerNumber()
{
	if (m_frequentFlyerNumber)
	{
		return std::optional<int>{m_frequentFlyerNumber};
	}
	else
	{
		return std::nullopt;
	}//m_frequentFlyerNumber ? m_frequentFlyerNumber : std::nullopt;
}
void setFrequentFlyerNumber(const bool freqNumber);