// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 * Subscriber.cpp
 *
 */

#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/subscriber/SubscriberImpl.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <fastdds/dds/topic/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/Topic.hpp>

#include <dds/domain/DomainParticipant.hpp>

using namespace eprosima;
using namespace eprosima::fastdds::dds;

Subscriber::Subscriber(
        const ::dds::domain::DomainParticipant& dp,
        const SubscriberQos& qos,
        SubscriberListener* listener,
        const ::dds::core::status::StatusMask& /*mask*/)
    : impl_(dp.delegate()->create_subscriber(qos, fastrtps::SubscriberAttributes(), listener /*, mask*/)->impl_)
{
}

const SubscriberQos& Subscriber::get_qos() const
{
    return impl_->get_qos();
}

ReturnCode_t Subscriber::get_qos(
        SubscriberQos& qos) const
{
    qos = impl_->get_qos();
    return ReturnCode_t::RETCODE_OK;
}

ReturnCode_t Subscriber::set_qos(
        const SubscriberQos& qos)
{
    return impl_->set_qos(qos);
}

const SubscriberListener* Subscriber::get_listener() const
{
    return impl_->get_listener();
}

SubscriberListener* Subscriber::get_listener()
{
    return impl_->get_listener();
}

ReturnCode_t Subscriber::set_listener(
        SubscriberListener* listener)
{
    return impl_->set_listener(listener);
}

DataReader* Subscriber::create_datareader(
        const TopicDescription& topic_desc,
        const DataReaderQos& reader_qos,
        DataReaderListener* listener,
        const ::dds::core::status::StatusMask& /*mask*/)
{
    Topic* topic = const_cast<DomainParticipant*>(get_participant())->find_topic(topic_desc.get_name(),
                    Duration_t(100, 0));
    if (topic == nullptr)
    {
        topic = const_cast<DomainParticipant*>(get_participant())->create_topic(topic_desc.get_name(),
                        topic_desc.get_type_name(), TOPIC_QOS_DEFAULT);
    }
    return impl_->create_datareader(*topic, reader_qos, listener);
}

DataReader* Subscriber::create_datareader(
        const Topic& topic,
        const DataReaderQos& qos,
        DataReaderListener* listener,
        const ::dds::core::status::StatusMask& /*mask*/)
{
    return impl_->create_datareader(topic, qos, listener);
}

ReturnCode_t Subscriber::delete_datareader(
        DataReader* reader)
{
    return impl_->delete_datareader(reader);
}

DataReader* Subscriber::lookup_datareader(
        const std::string& topic_name) const
{
    return impl_->lookup_datareader(topic_name);
}

ReturnCode_t Subscriber::get_datareaders(
        std::vector<DataReader*>& readers) const
{
    return impl_->get_datareaders(readers);
}

bool Subscriber::has_datareaders() const
{
    return impl_->has_datareaders();
}

/* TODO
   bool Subscriber::begin_access()
   {
    return impl_->begin_access();
   }
 */

/* TODO
   bool Subscriber::end_access()
   {
    return impl_->end_access();
   }
 */

ReturnCode_t Subscriber::notify_datareaders() const
{
    return impl_->notify_datareaders();
}

/* TODO
   bool Subscriber::delete_contained_entities()
   {
    return impl_->delete_contained_entities();
   }
 */

ReturnCode_t Subscriber::set_default_datareader_qos(
        const DataReaderQos& qos)
{
    return impl_->set_default_datareader_qos(qos);
}

const DataReaderQos& Subscriber::get_default_datareader_qos() const
{
    return impl_->get_default_datareader_qos();
}

ReturnCode_t Subscriber::get_default_datareader_qos(
        DataReaderQos& qos) const
{
    qos = impl_->get_default_datareader_qos();
    return ReturnCode_t::RETCODE_OK;
}

/* TODO
   bool Subscriber::copy_from_topic_qos(
        DataReaderQos& reader_qos,
        const fastrtps::TopicAttributes& topic_qos) const
   {
    return impl_->copy_from_topic_qos(reader_qos, topic_qos);
   }
 */

bool Subscriber::set_attributes(
        const fastrtps::SubscriberAttributes& att)
{
    return impl_->set_attributes(att);
}

const fastrtps::SubscriberAttributes& Subscriber::get_attributes() const
{
    return impl_->get_attributes();
}

const DomainParticipant* Subscriber::get_participant() const
{
    return impl_->get_participant();
}

const fastrtps::rtps::InstanceHandle_t& Subscriber::get_instance_handle() const
{
    return impl_->get_instance_handle();
}