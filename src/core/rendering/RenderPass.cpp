#include "core/rendering/RenderPass.h"

RenderPass::RenderPass()
{

}

RenderPass::~RenderPass()
{

}

void RenderPass::clean()
{
    vkDestroyRenderPass(m_info.logicalDevice->getLogicalDevice(), m_renderPass, nullptr);
}

void RenderPass::setData(const RenderPassCreateInfo& createInfo)
{
    m_info = createInfo;
}

int RenderPass::createRenderPass()
{
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format                  = m_info.swapChain->getImageFormat();
    colorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentReference  = {};
    colorAttachmentReference.attachment             = 0;
    colorAttachmentReference.layout                 = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass  = {};
    subpass.pipelineBindPoint     = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount  = 1;
    subpass.pColorAttachments     = &colorAttachmentReference;

    VkRenderPassCreateInfo renderPassCreateInfo = {};
    renderPassCreateInfo.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.attachmentCount        = 1;
    renderPassCreateInfo.pAttachments           = &colorAttachment;
    renderPassCreateInfo.subpassCount           = 1;
    renderPassCreateInfo.pSubpasses             = &subpass;

    if (vkCreateRenderPass(m_info.logicalDevice->getLogicalDevice(), &renderPassCreateInfo, nullptr, &m_renderPass) != VK_SUCCESS)
    {
        Logger::printError("RenderPass::createRenderPass", "vkCreateRenderpass failed!");

        return 1;
    }

    return 0;
}

int RenderPass::createRenderPass(RenderPass* renderPass, const RenderPassCreateInfo& createInfo)
{
    renderPass->setData(createInfo);

    return renderPass->createRenderPass();
}

RenderPass::RenderPassCreateInfo& RenderPass::getInfo()
{
  return m_info;
}