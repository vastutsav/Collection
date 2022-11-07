# Solar: 

Grid-tied solar falls under a ton of regulations, and may or may not provide much useful function when the grid is down. Do your own research, then come back here and add links! There's a ton over at /r/Solar of course. 

Off-grid solar is still done the way it's been done for decades, and has a lot in common with RV and marine electrical. There's a wealth of knowledge in the [Home Power magazine](https://www.homepower.com/) back-issues; though they stopped publishing in 2018, the last few years are still pretty relevant. Off-grid can be easy (a few 12 volt panels connected to 12 volt batteries connected to an inverter; around a few hundred dollars) or very, very complicated (80 amp MPPT connected to 48 volt 400 amp-hour parallel battery bank connected to a power center with internet monitoring; starts at around 5k and goes to infinity). Due to the large solutions space, it would be impossible to cover everything here, but sizing at
https://unboundsolar.com/solar-information/offgrid-calculator can give you a good idea on your needs.

If your needs are small or sporadic enough, a solar "generator" may be all you need. See also "batteries for medium loads", below. 

Here is an excellent thread on [stetting up a solar energy system](https://www.reddit.com/r/preppers/comments/8p5juq/solar_101_how_to_set_up_and_calculate_a_solar/) (dead link).

Here's an extensive checklist on how to design and size an off-grid solar with storage : https://www.leonics.com/support/article2_12j/articles2_12j_en.php.


# Generator:

See also, /r/Generator 

## Choosing a unit, types, capacity

Consider noise, fuel consumption, fuel storage, runtime, maintenance, and what loads you actually need to run. IMHO, aim smaller and curtail your loads, because the tradeoff in runtime is worth it. 

Conventional "synchronous" generators have to roar along at 3600rpm to make 60Hz power, regardless of load. If heavily loaded, this is fine, but if lightly loaded it means you're burning a ton of gas and making a ton of noise for no benefit. A typical 5000-7000W generator will burn about 1/2 to 1 gallon of gasoline per hour, and this only changes a little depending on load. 

"Inverter generators" (canonical example, the Honda eu2200i and friends) use an electronic inverter to make the 60Hz waveform regardless of the actual engine RPM. Flip the "eco mode" switch and the engine will throttle down to whatever's appropriate for the load. If heavily loaded, this might not change much, but lightly loaded it makes a huge difference. A typical 2000W inverter generator might burn 0.1 gallon per hour lightly loaded, up to 0.3 gallons per hour fully loaded. Noise scales with load, but these are generally very well shrouded and very quiet even fully loaded. 

Assume 10 gallons of stored fuel, which will last the inverter generator 3+ days, might not even carry a conventional unit through the first night. Consider your fuel storage situation before choosing a generator. And consider running it intermittently! Set up a freezer temperature alarm and use it as your time-to-start-the-generator alarm... 

## Fuel 

Gasoline isn't shelf-stable, it degrades in a few months if left untreated. Fuel treatment like Sta-Bil will extend that to a year or two, but you still need to pour the old gas into your car or something and refill the cans periodically, and _the more you store the more you need to refresh._ 

Diesel is a bit more shelf-stable, but will degrade within a year all the same. It also can be treated with stabilizer to expand it's shelf-life.
Diesel motors can also run on Waste Vegetable Oil (WVO): About every single diesel engine can run on a mixture of 30%WVO 70%Diesel without modification. Some engines, with modifications, will run on 100%WVO. 
WVO has to be filtered down to 1micrometer before use, to avoid clogging injectors. In theory, properly filtered and stored WVO will last several years (it actually depends on whats been cooked in it).

Propane is more expensive per unit energy, but it keeps forever as long as you can prevent the tank from rusting. 

TODO: Expand this section with info about getting fuel from your car's tank. I've heard that a "fuel rail pressure test kit" can make it easy to tap the downstream side of the fuel pump, then you let the pump just hand you the fuel, no siphoning required... 

## Maintenance

Most generators use older engine types that take 10W30 oil, while your car is likely to use something lighter like 5W20 or 0W20. This means you may be keeping a separate stash of oil around for maintenance. This also doesn't last forever on the shelf, so consider how much you want to stock. 

Yes, small engines need their oil changed a lot more often than cars. They don't have oil filters, so all the crud just ends up suspended in the oil. Change it just after a run, so it's all stirred up and you get most of the crud out! In a pinch, you can drain it, filter it, and pour it back in. 

There's probably more at /r/Generator or something. Click the Edit button and add more articles here!

# Batteries for small loads

(Batteries for large loads generally fall under "off-grid solar", above.)

A USB power-bank can be a convenient way to run small lights and fans, and charge phones and stuff, when utility power isn't available, or between periods of generator run. But the Achilles' heel of most USB power-banks is their slow recharge speed. If you fire up the generator for an hour, or visit a coffee shop with outlets for an hour, can you refill a depleted Anker? Not hardly! Barely even a little! 

Technical background: Without getting too deep into the electrical weeds, at the time of writing, most USB powerbanks can only charge over USB at 5v and maybe 2A, or possibly 9v or 12v at 1.5A if they support QuickCharge. Multiply volts times amps to get watts, so you're moving 10 to 18 watts. For a typical little "10,000mah (at unspoken 3.7v lithium voltage)" unit, that means it holds 37 watt-hours. If it's charging at 10 watts, you need roughly 4 hours to refill it from flat. (In practice somewhat longer because of efficiency loss and end-of-charge taper, but we're in the ballpark.) Larger powerbanks tend to exacerbate the "swimming pool through a drinking straw" problem, many needing overnight-or-more to refill their capacious batteries. 

Worse yet, USB charging is extremely hit-or-miss! Some cables just have thinner wires and higher resistance, and will only move a tiny fraction of the possible current. (In practice, I've seen the same source and the same load negotiate anything between 2.5W and 18W, the only difference being the cable.) And you have no visibility into this without a meter of some sort. Invest in one or two of the little USB charger-doctor meters; I like the UD18 for its versatility, it's about $25, but even the $5 OLED cheapies are a lot better than flying blind. 

With faster charging, you could make better use of occasional generator runs, to quickly store some power in your batteries, and then slowly use it on lights, fans, etc while the generator is stopped to save fuel and noise. 

The fastest-charging batteries most of us have around are __power-tool packs__. Whether you've got Ryobi or Kobalt, Milwaukee or Makita, DeWalt or Metabo, every brand has a $20-ish [USB-output cap](https://www.homedepot.com/s/18v%20usb?NCNI-5) you can slap onto the batteries. And power-tool chargers typically shove 40-plus watts into the pack, often achieving a full charge in under an hour. And many of us have accumulated multiple chargers, so we can load up that generator and really sock away some watt-hours while it's chilling the fridge down. 

Some brands also have small (150-watt is typical) AC inverters that'll run from the same battery pack. These aren't practical for much more than a laptop or a box fan, and of course a 150-watt load will suck dry a 70-watt-hour pack in half an hour or so. IMHO not too useful. 

# Batteries for medium loads

Jackery, Ego Nexus, Ecoflow, Goal Zero, et al. 

These products are often positioned as "generator replacement", although they can also complement a generator quite nicely. They typically store around 500-1500 watt-hours, and typically include an AC inverter sized roughly to the batteries' 1-hour capacity. So a unit with a 500 WH battery probably also has a 500W inverter or thereabouts, and can probably hold up a 500W load for slightly under an hour. (But not a 1W load for 500 hours -- there's some "idle load" consumed by the inverter simply for being on, regardless of connected loads, typically 3-8 watts.) 

Around the 1000W class and up, these units are capable of spinning a fridge compressor or some forced-air furnace blowers. But given that both fridges and furnaces tend to run for hours (especially if it's been a while and the thermostat has a _mighty need_), that'll still flatten the battery in short order and you'd better have a plan for recharging. 

They're also practical for heated blankets and things, but resistive heat is the definition of a power-hungry wasteful load. Space-heaters are right out -- you're just flattening the battery dumping heat into the cold walls of the house -- but a heating pad or blanket that delivers it right where it's used, that's a good way to get through the night with the generator stopped for quietude's sake, then restart it in the morning when you can supervise it. 

All of these type of units also include input connectors for attaching solar panels, since most of their components are common with what you'd find in an off-grid solar deployment anyway, it's sort of a no-brainer to provide the connector for panels too. The panels themselves can be bulky and expensive, and take a few minutes to set up, but it's hard to argue with power that's both silent and free. 

TODO: Anyone got a compatibility chart of connectors, voltages, and brands? Can you plug Goal Zero panels straight into a Jackery unit, or are there adapters required?


# Batteries for Heavy Loads

EG4, SOK, Jakiper, Trophy

These batteries are typically found in the &gt;4kWh range and can be used with some serious hardware. The folks over at r/SolarDIY can get more into it, but if you have a serious need for a long term off grid system, these are where you'd store all that juice. Charging can be done from an outlet, but charge times will be in the days; normally these would be connected directly to an MPPT charge controller rated for &gt;60 amps charging. Inverters at this point start at ~$500 and go to &gt;$5000.
