<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
              xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
              xmlns:xhtml="http://www.w3.org/1999/xhtml"
              version="1.0">
  <xsl:output method="text" version="1.0" encoding="UTF-8"
              media-type="text/plain" />

  <xsl:strip-space elements="*" />

  <xsl:template match="@*|node()">
    <xsl:apply-templates select="@*|node()"/>
  </xsl:template>

  <xsl:template match="xhtml:pre">
    <xsl:value-of select="text()"/>
  </xsl:template>
</xsl:stylesheet>
