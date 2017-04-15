// Copyright (c) 2017 Hypha

#include <hypha/plugin/hyphahandler.h>
#include <hypha/plugin/hyphaactor.h>
#include <hypha/plugin/hyphasensor.h>
#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/pluginutil.h>

using namespace hypha::plugin;

bool PluginUtil::isHandler(HyphaBasePlugin *plugin)
{
    if(dynamic_cast<HyphaHandler*>(plugin))
        return true;
    return false;
}

bool PluginUtil::isActor(HyphaBasePlugin *plugin)
{
    if (dynamic_cast<HyphaActor*>(plugin))
        return true;
    return false;
}

bool PluginUtil::isSensor(HyphaBasePlugin *plugin)
{
    if (dynamic_cast<HyphaSensor*>(plugin))
        return true;
    return false;
}

bool PluginUtil::isReceiver(HyphaBasePlugin *plugin)
{
    if (dynamic_cast<HyphaReceiver*>(plugin))
        return true;
    return false;
}

bool PluginUtil::isSender(HyphaBasePlugin *plugin)
{
    if (dynamic_cast<HyphaSender*>(plugin))
        return true;
    return false;
}
